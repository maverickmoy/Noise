#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <sstream> 
#include <vector>
using namespace std;

double numSamples;

// Pink Noise generation (Bonus)
double generatePinkNoise(long long step) {
    // Buffer for pink noise, using 6 stages b[0]-b[5]
    static double b[7] = {0};

    // Generate white noise
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    double whiteNoiseSample = dist(engine);

    // Apply filter stages to white noise (Paul Kellet's refined method)
    b[0] = 0.99886 * b[0] + whiteNoiseSample * 0.0555179;
    b[1] = 0.99332 * b[1] + whiteNoiseSample * 0.0750759;
    b[2] = 0.96900 * b[2] + whiteNoiseSample * 0.1538520;
    b[3] = 0.86650 * b[3] + whiteNoiseSample * 0.3104856;
    b[4] = 0.55000 * b[4] + whiteNoiseSample * 0.5329522;
    b[5] = -0.7616 * b[5] - whiteNoiseSample * 0.0168980;
    double pinkNoiseSample = b[0] + b[1] + b[2] + b[3] + b[4] + b[5] + b[6] + whiteNoiseSample * 0.5362;
    b[6] = whiteNoiseSample * 0.115926;

    return pinkNoiseSample * 0.11; // Scaling factor to keep the result in the range of -1 to 1
}


double generateBrownianNoise(long long step) {    
    
    // Generate white noise sample   
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    double whiteNoiseSample = dist(engine);
    

    // Integrate (accumulate) the white noise to generate Brownian noise
    int numSamples = 1000; // Define the number of samples
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.5, 0.5);

    std::vector<double> brownNoise(numSamples);
    double currentVal = 0.0;

    for (int i = 0; i < numSamples; ++i) {
        currentVal += dis(gen);
        brownNoise[i] = currentVal;
    }


    // Return the current Brownian noise sample

    return 0;   
}

// Main function
int main() {

double numsamples;

    // Define the duration in seconds and the number of microseconds per second
    const int seconds = 1; // Play around with numbers
    const int milisecondsPerSecond = 1000; // Play around with numbers

    // Calculate the number of steps (microseconds) in the given seconds
    long long totalSteps = seconds * milisecondsPerSecond;

    // Initialize random number generator for white noise between -1.0 and 1.0
    random_device rd;
    default_random_engine engine(rd());
    uniform_real_distribution<double> dist(-1.0, 1.0); //Amplitude -1.0 to 1.0

    // Set the frequency for the sine wave (10 Hz)
    const double frequency = 10.0; //Hz // Play around with numbers
    const double sampleRate = milisecondsPerSecond;  // 1 sample per milisecond
    const double angularFrequency = 2.0 * M_PI * frequency;  // Angular frequency (2 * Pi * f)

    // Open CSV files to save the noise samples
    ostringstream filename;
    
    // **!** Change file names to frequency number. If you do 100Hz then change pure_signal_10Hz_ to pure_signal_10Hz_
    // File 1: Stand-alone signal (pure 10Hz sine wave)
    filename.str("pure_signal_10Hz_");
    filename << "pure_signal_10Hz_" << seconds << "_samples.csv";
    ofstream fileSignal(filename.str());
    fileSignal << "Step,Signal" << endl;

    // File 2: White noise added to the signal
    filename.str("white_noise_added_10Hz_");
    filename << "white_noise_added_10Hz_" << seconds << "_samples.csv";
    ofstream fileWhiteNoise(filename.str());
    fileWhiteNoise << "Step,Signal" << endl;

    // File 3: Brownian noise added to the signal
    filename.str("brownian_noise_added_10Hz_");
    filename << "brownian_noise_added_10Hz_" << seconds << "_samples.csv";
    ofstream fileBrownianNoise(filename.str());
    fileBrownianNoise << "Step,Signal" << endl;

    // File 4: Pink noise added to the signal (Bonus)
    filename.str("pink_noise_added_10Hz_");
    filename << "pink_noise_added_10Hz_" << seconds << "_samples.csv";
    ofstream filePinkNoise(filename.str());
    filePinkNoise << "Step,Signal" << endl;

    // File 5: White + Brownian noise added to the signal
    filename.str("white_brownian_noise_added_10Hz_");
    filename << "white_brownian_noise_added_10Hz_" << seconds << "_samples.csv";
    ofstream fileWhiteBrownianNoise(filename.str());
    fileWhiteBrownianNoise << "Step,Signal" << endl;

    // File 6: White + Brownian + Pink noise added to the signal (Bonus)
    filename.str("white_brownian_pink_noise_added_10Hz_");
    filename << "white_brownian_pink_noise_added_10Hz_" << seconds << "_samples.csv";
    ofstream fileWhiteBrownianPinkNoise(filename.str());
    fileWhiteBrownianPinkNoise << "Step,Signal" << endl;


    // Generate the signals and write to files
    for (long long i = 0; i < totalSteps; ++i) {
        // A. Signal generation
        // Generate my signal 
        double sineWaveSample = sin(angularFrequency * 1.5 * i / sampleRate); 

        // Generate white noise sample
        double whiteNoiseSample = dist(engine); // Study this! Make sure you know how this works! Write about it in the paper.

        // Generate Brownian noise sample 
        double brownianNoiseSample = generateBrownianNoise(i);

        // Generate pink noise (Bonus)
        double pinkNoiseSample = generatePinkNoise(i);

        // B. Noise addition & Saving to files
        // Combine signals and write to the respective files
        fileSignal << i << "," << sineWaveSample << endl;

        // White noise added to sine wave
        fileWhiteNoise << i << "," << sineWaveSample + whiteNoiseSample << endl;

        // Brownian noise added to sine wave
        fileBrownianNoise << i << "," << sineWaveSample + brownianNoiseSample << endl;


        // C. Bonus: Pink noise addition & Saving to files
        // White and brownian noise added to sine wave (Bonus)
        fileWhiteBrownianNoise << i << "," << sineWaveSample + whiteNoiseSample + brownianNoiseSample << endl;
        
        // Pink noise added to sine wave (Bonus)
        filePinkNoise << i << "," << sineWaveSample + pinkNoiseSample << endl;
        
        // White, brownian, and pink noise added to sine wave (Bonus)
        fileWhiteBrownianPinkNoise << i << "," << sineWaveSample + whiteNoiseSample + brownianNoiseSample + pinkNoiseSample << endl;
    }

    cout << "Generated " << totalSteps << " samples for " << seconds << " seconds with various noise configurations." << endl;

    return 0;
}
