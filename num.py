import numpy as np
import matplotlib.pyplot as plt

with open("data.txt", "r") as file:
    a = [float(i) for i in file.read().split("\n")]

data_array =np.loadtxt("data.txt", dtype=int)

print(data_array)

x = np.linspace(0, 5, 100)
fig, ax = plt.subplots(figsize = (6,4), dpi = 280)
ax.plot(x, linewidth = 2)
ax.plot(x, color = 'blue')

ax.minorticks_on()    
ax.grid(which = 'major',color = 'black',    #  цвет главной сетки
        linewidth = 0.5,    #  толщина
        linestyle = '-')    #  начертание
ax.grid(which = 'minor',color = 'gray',    #  цвет доп. сетки
        linewidth = 0.5,    #  толщина
        linestyle = '-.')    #  начертание

ax.plot(data_array)


#  Добавляем подписи к осям:
ax.set_xlabel('Время Т (С)')
ax.set_ylabel('Напряжение U (В)')
# Добавили название графика
ax.set_title('График зарядки/разрядки конденсатора')
# + Легенда
lgnd = ax.legend(['U(t)'], loc='upper right', shadow=True)
ax.text(80, 220, 'Время зарядки = 4.21 c', fontsize = 5, color = 'blue')
ax.text(80, 210, 'Время разрядки =5.65 c', fontsize = 5, color = 'blue')
plt.plot(range(0,10), range(0,10))
plt.show()
