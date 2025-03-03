import matplotlib.pyplot as plt
import pandas as pd


#  ================================================================================
#  ||                                                                            ||
#  ||              Assignment 4 part 1                                           ||
#  ||              ------------------------------------------------------        ||
#  ||              Signal and Noise                                              ||
#  ||                                                                            ||
#  ||              D E M O N S T R A T I O N   C O D E                           ||
#  ||              ------------------------------------------------------        ||
#  ||                                                                            ||
#  ||                     Developed by: Paul Hoffmann                            ||
#  ||                     California State University, San Marcos                ||
#  ||                                                                            ||
#  ||                For: CS111 for California State University, San Marcos      ||
#  ||                                                                            ||
#  ||           Copyright 2025 Paul Hoffmann                                     ||
#  ||                                                                            ||
#  ||                     Not for distribution or use outside of the             ||
#  ||                     this course.                                           ||
#  ||                                                                            ||
#  ================================================================================


# List of CSV files to plot. Make sure to update file names!
csv_files = [
    'pure_signal_10Hz_1_samples.csv',
    'white_noise_added_10Hz_1_samples.csv',
    'pink_noise_added_10Hz_1_samples.csv',
    'brownian_noise_added_10Hz_1_samples.csv',
    'white_brownian_pink_noise_added_10Hz_1_samples.csv'
]

# Titles for the plots. Make sure to update Title names!
titles = [
    'Pure 10 Hz Signal',
    'White Noise + 10 Hz Sine Wave',
    'Pink Noise + 10 Hz Sine Wave',
    'Brownian Noise + 10 Hz Sine Wave',
    'White & Brown & Pink Noise + 10 Hz Sine Wave'
]

# Iterate over the CSV files and create plots
for i, csv_file in enumerate(csv_files):
    data = pd.read_csv(csv_file)

    plt.figure(figsize=(10, 6))

    plt.plot(data['Step'], data['Signal'], label=f"Signal: {titles[i]}", color='blue', alpha=0.6)

    plt.title(titles[i])
    plt.xlabel('Time Step (Miliseconds)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.legend()


    plt.savefig(f"{csv_file.replace('.csv', '.png')}")
    plt.close() 

    print(f"Saved plot for {csv_file} as PNG.")

print("All plots generated and saved as PNG files.")
