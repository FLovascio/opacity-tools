#include "Conductivity.hxx"
#include "Opacity.hxx"
#include "FileIO.hxx"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

inline bool file_exists(const std::string &name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

inline bool directory_exists(const std::string &dir) {
  return (access(dir.c_str(), (bool)R_OK && (bool)W_OK) == 0);
}

int main(int argc, char **argv) {
  // read directory name from argv
  std::string dir = "./";
  bool useLocal = true;
  bool binaryOutput = true;
  std::string outputDir = "./";
  bool doublePrecision = true;
  std::string distributionFile;
  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    if (arg == "-h" || arg == "--help") {
      std::cout
          << "Help will always be given at Hogwarts to those who ask for it..."
          << "\n"
          << "But you are not in Hogwarts, are you?\n";
      return 0;
    }
    if (arg == "--from_dir" || arg == "-d") {
      useLocal = false;
      if ((i + 1) == argc) {
        std::cerr << "\033[1;31mARGUMENT ERROR: NO DIRECTORY PROVIDED!\033[0m "
                     "Argument --from_dir/-d must be followed by a directory\n";
        return 1;
      }
      dir = std::string(argv[i + 1]);
      if (!(file_exists(dir + "material_abundancies.dat"))) {
        std::cerr << "\033[1;31mARGUMENT ERROR: INVALID DIRECTORY!\033[0m the "
                     "directory provided is: "
                  << dir
                  << " this is either not a valid directory or does not "
                     "contain a material_abundancies.dat file.\n";
        return 1;
      }
      ++i;
    }
    if (arg == "--output_dir" || arg == "-o") {
      useLocal = false;
      if ((i + 1) == argc) {
        std::cerr
            << "\033[1;31mARGUMENT ERROR: NO DIRECTORY PROVIDED!\033[0m "
               "Argument --output_dir/-o must be followed by a directory\n";
        return 1;
      }
      outputDir = std::string(argv[i + 1]);
      if (!(directory_exists(outputDir))) {
        std::cerr << "\033[1;31mARGUMENT ERROR: INVALID DIRECTORY!\033[0m the "
                     "output directory provided is: "
                  << dir
                  << " this is not a valid directory, check the directory and "
                     "permissions.\n";
        return 1;
      }
      ++i;
    }
    if (arg == "-b" || arg == "--binary_output") {
      std::cout << "Binary output is default!\n";
    }
    if (arg == "--text_output") {
      binaryOutput = false;
      std::cerr
          << "\033[1;33mWARNING: PLAIN TEXT OUTPUT!\033[0m Output format is "
             "set to plain text. This will hurt performance for large files.\n";
    }
    if (arg == "--FP32") {
      doublePrecision = false;
      std::cerr << "\033[1;33mWARNING: SINGLE PRECISION!\033[0m Compute has "
                   "been set to single precision.\n";
    }
  }
  distributionFile=dir+"dust_size_distribution.dat";
  if (doublePrecision) {
    conductivity::mixedGrain<double> grain(
        conductivity::readGrainFromSetup(dir, 1e-4));
    conductivity::solveSystem<double>(grain);
    if(file_exists(distributionFile)){       
    }
    else{
        std::cerr<<"\033[1;31mIO ERROR: distributionFile cannot be opened!\033[0m \n";
        return 1;
    }
    dust::dustDistribution<double> dustDist(distributionFile,distributionFile);
    std::vector<double> KDust=opacity::KappaDust<double>(grain.lambda_k,grain.sigma_eff_j,dustDist);
    if (binaryOutput) {
      binaryFiles::writeComplexVectorToBinary<double>(
          grain.sigma_eff_j, outputDir + "EffectiveConductivities.bin");
      binaryFiles::writeRealVectorToBinary<double>(grain.lambda_k,
                                                   outputDir + "Lambda.bin");
      binaryFiles::writeRealVectorToBinary<double>(KDust,outputDir+"Opacities.bin");
    } else {
      delimitedFiles::writeComplexVectorToFile<double>(
          grain.sigma_eff_j, outputDir+"EffectiveConductivities.csv");
      delimitedFiles::writeRealVectorToFile<double>(grain.lambda_k,
                                                    outputDir+"Lambda.csv");
      delimitedFiles::writeRealVectorToFile<double>(KDust,outputDir+"Opacities.csv");
    }
  } else {
    conductivity::mixedGrain<float> grain=
        conductivity::readGrainFromSetup<float>(dir, 1e-4);
    conductivity::solveSystem<float>(grain);
    if(file_exists(distributionFile)){
    }
    else{
        std::cerr<<"\033[1;31mIO ERROR: distributionFile cannot be opened!\033[0m \n";
        return 1;
    }
    dust::dustDistribution<float> dustDist(distributionFile,distributionFile);
    std::vector<float> KDust=opacity::KappaDust<float>(grain.lambda_k,grain.sigma_eff_j,dustDist);
    if (binaryOutput) {
      binaryFiles::writeComplexVectorToBinary<float>(
          grain.sigma_eff_j, outputDir + "EffectiveConductivities.bin");
      binaryFiles::writeRealVectorToBinary<float>(grain.lambda_k,
                                                   outputDir + "Lambda.bin");
      binaryFiles::writeRealVectorToBinary<float>(KDust,outputDir+"Opacities.bin");
    } else {
      delimitedFiles::writeComplexVectorToFile<float>(
          grain.sigma_eff_j, outputDir+"EffectiveConductivities.csv");
      delimitedFiles::writeRealVectorToFile<float>(grain.lambda_k,
                                                    outputDir+"Lambda.csv");
      delimitedFiles::writeRealVectorToFile<float>(KDust,outputDir+"Opacities.csv");
    }
  }
  return 0;
}
