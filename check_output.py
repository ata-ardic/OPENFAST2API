import netCDF4 as nc
import numpy as np
import matplotlib.pyplot as plt

# Open the NetCDF file (update the filename if necessary)
filename = 'build/turb_01_output.nc'
ds = nc.Dataset(filename, mode='r')

# Check available variables (for verification)
print("Available variables in output file:", ds.variables.keys())

# Read the hub_rotvel variable
hub_rotvel = ds.variables['hub_rotvel'][:]
print("Shape of hub_rotvel:", hub_rotvel.shape)
print("Sample hub_rotvel data:")
print(hub_rotvel)

# Assuming hub_rotvel is a 2D array with dimensions (time, components),
# and you want to plot each component versus time:
time = ds.variables['time'][:]  # get the time array

plt.figure(figsize=(10, 5))
if hub_rotvel.ndim == 2 and hub_rotvel.shape[1] >= 3:
    plt.plot(time, hub_rotvel[:, 0], label='X component')
    plt.plot(time, hub_rotvel[:, 1], label='Y component')
    plt.plot(time, hub_rotvel[:, 2], label='Z component')
    plt.xlabel('Time (s)')
    plt.ylabel('Hub Rotational Velocity (rad/s)')
    plt.title('Hub Rotational Velocity vs Time')
    plt.legend()
else:
    # If hub_rotvel is one-dimensional or has a different structure:
    plt.plot(time, hub_rotvel, label='Hub Rotational Velocity')
    plt.xlabel('Time (s)')
    plt.ylabel('Hub Rotational Velocity')
    plt.title('Hub Rotational Velocity vs Time')
    plt.legend()

plt.show()

# Always remember to close the dataset
ds.close()
