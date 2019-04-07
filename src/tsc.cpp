#include <fstream>
#include <iostream>
#include <cstdint>
#include "args.hpp"

bool Decrypt(const std::string& fname, const std::string& fname_out)
{
    int fsize, i;
    std::ifstream ifs;
    std::ofstream ofs;

    ifs.open (fname, std::ifstream::binary);

    if (!ifs)
    {
        std::cerr << "tsc_decrypt: no such file: " << fname << std::endl;
        return false;
    }

    ofs.open (fname_out, std::ifstream::binary);

    if (!ofs)
    {
        std::cerr << "tsc_decrypt: can't open file: " << fname << std::endl;
        return false;
    }

    ifs.seekg (0, ifs.end);
    fsize = ifs.tellg();
    ifs.seekg (0, ifs.beg);

    // load file
    uint8_t *buf = new uint8_t[fsize];
    ifs.read((char*)buf, fsize);
    ifs.close();

    // get decryption key, which is actually part of the text
    int keypos = (fsize / 2);
    uint8_t key = buf[keypos];

    // everything EXCEPT the key is encrypted
    for(i=0;i<keypos;i++) { buf[i] = (buf[i] - key); }
    for(i++;i<fsize;i++)  { buf[i] = (buf[i] - key); }

    ofs.write((char*)buf, fsize);
    ofs.close();

    return true;
}

bool Encrypt(const std::string& fname, const std::string& fname_out)
{
    int fsize, i;
    std::ifstream ifs;
    std::ofstream ofs;

    ifs.open (fname, std::ifstream::binary);

    if (!ifs)
    {
        std::cerr << "tsc_encrypt: no such file: " << fname << std::endl;
        return false;
    }

    ofs.open (fname_out, std::ifstream::binary);

    if (!ofs)
    {
        std::cerr << "tsc_encrypt: can't open file: " << fname << std::endl;
        return false;
    }

    ifs.seekg (0, ifs.end);
    fsize = ifs.tellg();
    ifs.seekg (0, ifs.beg);

    // load file
    uint8_t *buf = new uint8_t[fsize];
    ifs.read((char*)buf, fsize);
    ifs.close();

    // get decryption key, which is actually part of the text
    int keypos = (fsize / 2);
    uint8_t key = buf[keypos];

    // everything EXCEPT the key is encrypted
    for(i=0;i<keypos;i++) { buf[i] = (buf[i] + key); }
    for(i++;i<fsize;i++)  { buf[i] = (buf[i] + key); }

    ofs.write((char*)buf, fsize);
    ofs.close();

    return true;
}

int main(int argc, char *argv[])
{
  args::ArgumentParser parser("TSC encryptor/decryptor.", "");
  parser.helpParams.proglineShowFlags = true;

  args::HelpFlag arg_help(parser, "help", "Display this help menu", {'h', "help"});

  args::Positional<std::string> arg_in_file(parser, "input", "Path to input file.", args::Options::Required);
  args::Positional<std::string> arg_out_file(parser, "output", "Path to output file.", args::Options::Required);
  args::Flag arg_decrypt(parser, "decrypt", "Decrypt file instead of encrypting.", {'d'});

  try
  {
    parser.ParseCLI(argc, argv);
  }
  catch (args::Help&)
  {
    std::cout << "Usage:\n" << parser;
    return -1;
  }
  catch (args::ParseError& e)
  {
    std::cerr << e.what() << std::endl;
    std::cout << "\n\nUsage:\n" << parser;
    return -1;
  }
  catch (args::ValidationError& e)
  {
    std::cerr << e.what() << std::endl;
    std::cout << "\n\nUsage:\n" << parser;
    return -1;
  }

  if (arg_decrypt)
  {
    return Decrypt(args::get(arg_in_file),args::get(arg_out_file));
  }
  else
  {
    return Encrypt(args::get(arg_in_file),args::get(arg_out_file));
  }

  return 0;
}