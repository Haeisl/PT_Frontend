import sys
import matplotlib
matplotlib.use('Agg')  # For headless environments
import matplotlib.pyplot as plt
import numpy as np

def main():
    # Check if the correct number of arguments are provided
    if len(sys.argv) < 9:
        print("Usage: python GenerateHistogram.py <data_csv_path> <output_png_path> <num_bins> <bool_log_scale> <bool_constrain_xmin> <float_xmin> <bool_constrain_xmax> <float x_max> <bool_grid_lines>")
        sys.exit(1)

    # Parse command-line arguments
    data_csv_path = sys.argv[1]
    output_png_path = sys.argv[2]
    num_bins = int(sys.argv[3])
    log_scale = sys.argv[4].lower() == 'true'
    constrain_x_min = sys.argv[5].lower() == 'true'
    x_min = float(sys.argv[6]) if constrain_x_min else None
    constrain_x_max = sys.argv[7].lower() == 'true'
    x_max = float(sys.argv[8]) if constrain_x_max else None
    grid_lines = sys.argv[9].lower() == 'true'

    # Load the data from the CSV file
    data = []
    with open(data_csv_path, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                value = float(line)
                # Apply x-axis constraints if specified
                if (x_min is None or value >= x_min) and (x_max is None or value <= x_max):
                    data.append(value)

    # Convert the data list to a numpy array
    data = np.array(data)

    # Enable dark mode for the plot
    plt.style.use('dark_background')

    # Create the histogram plot
    plt.figure(figsize=(4.27, 2.4), dpi=300)
    plt.hist(data, bins=num_bins, edgecolor='white', color='#1f77b4', log=log_scale)
    plt.title("Histogram", fontsize=10, color='white')
    plt.xlabel("Value", fontsize=8, color='white')
    plt.ylabel("Frequency", fontsize=8, color='white')

    # Add grid lines if specified
    if grid_lines:
        plt.grid(visible=True, which="both", axis='both', linestyle="--", linewidth=0.3, color="white", alpha=0.5)

    # Adjust layout to fit elements properly
    plt.tight_layout()

    # Save the histogram as a PNG file
    plt.savefig(output_png_path, dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == "__main__":
    main()