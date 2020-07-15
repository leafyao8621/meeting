import mysql.connector

conn = None
cur = None

def initialize():
    global conn
    global cur
    conn = mysql.connector.connect(user="temp", password="tmep_eptm",
                                   host="localhost", database="Temp")
    cur = conn.cursor()

def schedule(verbose, fn):
    fout = None
    if (verbose and fn != "stdout"):
        fout = open(fn, "w")
    cur.execute("SELECT * FROM Meetings GROUP BY id ORDER BY start_time ASC")
    out = 0
    allocation = []
    for i in cur:
        j = 0
        while (j < out and i[1] < allocation[j]):
            j = j + 1
        if (j == out):
            out += 1
            allocation.append(i[2])
        else:
            allocation[j] = i[2]
        if (verbose):
            if (fout):
                print(f"id: {i[0]} start: {i[1]} end: {i[2]} assignment: {j}",
                      file=fout)
            else:
                print(f"id: {i[0]} start: {i[1]} end: {i[2]} assignment: {j}")
    if (fout):
        fout.close()
    return out

def finalize():
    cur.close()
    conn.close()
