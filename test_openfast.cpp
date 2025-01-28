#include <mpi.h>
#include "OpenFAST.H"
#include <iostream>
#include <string>
void debugInputs(const fast::fastInputs &inputs) {
    std::cout << "===== Debugging fastInputs =====" << std::endl;
    std::cout << "Number of Turbines (nTurbinesGlob): " << inputs.nTurbinesGlob << std::endl;
    std::cout << "Dry Run: " << std::boolalpha << inputs.dryRun << std::endl;
    std::cout << "Debug Mode: " << std::boolalpha << inputs.debug << std::endl;
    std::cout << "Time Step (dtFAST): " << inputs.dtFAST << std::endl;
    std::cout << "Max Simulation Time (tMax): " << inputs.tMax << std::endl;

    for (size_t i = 0; i < inputs.globTurbineData.size(); ++i) {
        const auto &turb = inputs.globTurbineData[i];
        std::cout << "Turbine " << i << ":" << std::endl;
        std::cout << "  Turbine ID: " << turb.TurbID << std::endl;
        std::cout << "  FAST Input File: " << turb.FASTInputFileName << std::endl;
        std::cout << "  Turbine Base Position: ";
        for (const auto &pos : turb.TurbineBasePos) std::cout << pos << " ";
        std::cout << std::endl;
        std::cout << "  Simulation Type: " << turb.sType << std::endl;
        std::cout << "  Number of Blades: " << turb.numBlades << std::endl;
        std::cout << "  Velocity Nodes per Blade: " << turb.numVelPtsBlade << std::endl;
        std::cout << "  Velocity Nodes on Tower: " << turb.numVelPtsTwr << std::endl;
        std::cout << "  Restart File: " << turb.FASTRestartFileName << std::endl;
        std::cout << "  Output File Root: " << turb.outFileRoot << std::endl;
        std::cout << "fast::EXTINFLOW = " << fast::EXTINFLOW << std::endl;
        std::cout << "FAST Input File: " << inputs.globTurbineData[0].FASTInputFileName << std::endl;

    }
    std::cout << "===== End Debugging fastInputs =====" << std::endl;
}

int main(int argc, char **argv) {
    // Initialize MPI
    std::cout << "Initializing MPI..." << std::endl;
    MPI_Init(&argc, &argv);
    std::cout << "MPI initialized successfully." << std::endl;

    try {
        // Define the path to the .fst file
        //std::string fstFilePath = "/home/inflows/Documents/OpenFAST/reg_tests/r-test/glue-codes/openfast/MinimalExample/Main.fst";
        std::string fstFilePath = "/home/inflows/Documents/OPENFAST2API/build/MyFAST.fst";
        std::cout << "Loading file: " << fstFilePath << std::endl;

        //std::string fstFilePath = "/home/inflows/Documents/OpenFAST/reg_tests/r-test/glue-codes/openfast/Ideal_Beam_Fixed_Free_Linear/Ideal_Beam_Fixed_Free_Linear.fst";
        // Set up OpenFAST input configuration
        fast::fastInputs inputs;
        inputs.nTurbinesGlob = 1;
        inputs.dryRun = false;  // For testing initialization
        inputs.debug = true;
        //inputs.dtFAST = 0.01;
        //inputs.tMax = 10.0;
        inputs.simStart = fast::init;
        inputs.comm = MPI_COMM_SELF;


        // Configure turbine-specific data
        fast::turbineDataType turbine;
        turbine.TurbID = 0;
        turbine.FASTInputFileName = fstFilePath;
        turbine.TurbineBasePos = {0.0, 0.0, 0.0};
        turbine.TurbineHubPos = {0.0, 0.0, 90.0};  // Hub position (explicitly set)
        
        turbine.sType = fast::EXTINFLOW;
        turbine.numBlades = 3; // Set based on your turbine
        turbine.numVelPtsBlade = 20; // AeroDyn nodes per blade
        turbine.numVelPtsTwr = 10;   // AeroDyn nodes on tower
        turbine.FASTRestartFileName = ""; // Empty if not restarting
        turbine.outFileRoot = "test_output";
        turbine.sType = fast::EXTINFLOW;
        inputs.globTurbineData.push_back(turbine);
        //inputs.globTurbineData[0].DT_Out = 0.05; // Set explicitly if required


        // Check MPI Communicator
        int rank, size;
        MPI_Comm_rank(inputs.comm, &rank);
        MPI_Comm_size(inputs.comm, &size);
        std::cout << "MPI Communicator: Rank = " << rank << ", Size = " << size << std::endl;

        // Create an OpenFAST instance
        fast::OpenFAST openFASTInstance;
        debugInputs(inputs);
        
        // Set inputs and initialize OpenFAST
        std::cout << "Setting OpenFAST inputs..." << std::endl;
        openFASTInstance.setInputs(inputs);
        std::cout << "Inputs set successfully!" << std::endl;

        std::cout << "Initializing OpenFAST simulation..." << std::endl;
        openFASTInstance.init();
        std::cout << "OpenFAST simulation initialized successfully!" << std::endl;

        // Dry run only - no simulation steps
        std::cout << "Dry run completed successfully!" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        MPI_Abort(MPI_COMM_SELF, EXIT_FAILURE);
    }

    // Finalize MPI
    MPI_Finalize();
    std::cout << "MPI finalized successfully." << std::endl;

    return EXIT_SUCCESS;
}
