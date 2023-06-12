```
import tkinter as tk
from tkinter import *
import os

root = tk.Tk()

HEIGHT = 700
WIDTH = 800

canvas = tk.Canvas(root, height=HEIGHT, width=WIDTH, bg="#80c1ff")
# canvas.place(relwidth=0.8, relheight=0.8, relx=0.05, rely=0.05)
canvas.pack()

frame = tk.Frame(root, bg="white")
frame.place(relwidth=1.0, relheight=1.0, relx=0.0, rely=0.0)

# three widgets: button, label, entry
header = tk.Label(frame, text="Welcome to the Roadside Drone Application!", font=('Courier', 20), bg='white')
header.place(relx=0.0, rely=0.0, relheight=0.1)

location = tk.Label(frame, text="Describe your current location: ", font=('Courier', 10), bg='white')
location.place(relx=0.0, rely=0.2, relheight=0.025)

locationEntry = tk.Text(frame, bg='white')
locationEntry.place(relx=0.0, rely=0.226, relheight=0.05, relwidth=0.3)

situation = tk.Label(frame, text="Describe your needs: ", font=('Courier', 10), bg='white')
situation.place(relx=0.0, rely=0.3, relheight=0.025)

situationEntry = tk.Text(frame, bg='white')
situationEntry.place(relx=0.0, rely=0.326, relheight=0.05, relwidth=0.3)

enterButton = tk.Button(root, text="Enter", padx=10, pady=5, 
                        fg="white", bg="#80c1ff")   
enterButton.place(relx=0.0, rely=0.375, relheight=0.04, relwidth=0.09)

nearestGas = tk.Label(frame, text="Your distance from the nearest gas station: ", 
                        font=('Courier', 10), bg='white')
nearestGas.pack(side='left')

root.mainloop()
```