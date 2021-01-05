### 20184646 권석환
### Navigator Client 프로그램

import socket
import tkinter as tk


# main window of our calculator
window = tk.Tk()
window.title("Created by 20184646 권석환")
window.geometry("300x250")

# search function for finding the shortest path
def search():
    res_box.delete(1.0,"end")
    HOST = '127.0.0.1'
    PORT = 8000
    path = first_nr.get() + '/' + second_nr.get()
    path = path.encode('UTF-8')
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(path)
        data = s.recv(1024)
        
    res_box.insert(tk.INSERT, data.decode('UTF-8'))


# all elements inside the window
lbl_nr_one = tk.Label(window, text="Enter the START:", bg="green")
lbl_nr_one.pack(padx=5, pady=5)

first_nr = tk.Entry(window, width=10)
first_nr.pack(padx=5, pady=5)

lbl_nr_two = tk.Label(window, text="Enter the END:", bg="red")
lbl_nr_two.pack(padx=10, pady=5)

second_nr = tk.Entry(window, width=10)
second_nr.pack(padx=10, pady=5)

button_search = tk.Button(window, text="Search shortest path!", command=search)
button_search.pack()

lbl_res = tk.Label(window, text="경로 / 거리")
lbl_res.pack(padx=10, pady=5)

res_box = tk.Text(window, width=15, height=1)
res_box.pack(padx=10, pady=5)

window.mainloop()
