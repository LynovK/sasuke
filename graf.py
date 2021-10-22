import matplotlib.pyplot as plt
measured_data = [10, 23, 45, 65, 23, 144, 165, 289]
plt.plot(measured_data)
#plt.show()

measured_data_str = [str(item) for item in measured_data]
print(measured_data, measured_data_str)

with open("data.txt", "r") as file:
 a = file.read("\n".join(measured_data_str))