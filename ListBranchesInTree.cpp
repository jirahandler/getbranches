#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <root_filename> <output_filename>" << std::endl;
        return 1;
    }

    const char *root_filename = argv[1];
    const char *output_filename = argv[2];

    TFile *file = TFile::Open(root_filename);
    if (!file || file->IsZombie())
    {
        std::cerr << "Error: cannot open file " << root_filename << std::endl;
        return 1;
    }

    TTree *tree = (TTree *)file->Get("AnalysisMiniTree");
    if (!tree)
    {
        std::cerr << "Error: cannot find tree 'AnalysisMiniTree' in the file" << std::endl;
        file->Close();
        return 1;
    }

    std::ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        std::cerr << "Error: cannot open output file " << output_filename << std::endl;
        file->Close();
        return 1;
    }

    TObjArray *branches = tree->GetListOfBranches();
    for (int i = 0; i < branches->GetEntries(); ++i)
    {
        TBranch *branch = (TBranch *)branches->At(i);
        output_file << branch->GetName() << std::endl;
    }

    output_file.close();
    file->Close();

    std::cout << "Branch names written to " << output_filename << std::endl;

    return 0;
}
