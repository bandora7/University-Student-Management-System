from cs50 import SQL
import csv

db = SQL("sqlite:///univ.db")
file = "temp.csv"


def insert(student_id, fname, lname, depa,  year, gpa):

    db.execute("INSERT INTO stu(stu_id, fname, lname, depa,  year, gpa) VALUES(?, ?, ?, ?, ?, ?)",
                                 student_id, fname, lname, depa, year, gpa)

def display(table, search=False, name="none"):

    
    if search :
        name =  name + "%" 
        rows = db.execute("SELECT * FROM ? WHERE fname LIKE ?", table, name)
    else:
        rows = db.execute("SELECT * FROM ?", table)
    
    records = []
    if rows :
        for i in range(len(rows)):
            del   rows[i]["id"]
        header = list(rows[0].keys())
        for i in rows:
            records.append(i.values())
        records = list(records)
    
    with open(file , 'w') as csvfile :
        write = csv.writer(csvfile)
        # write.writerow(header)
        # print(records)
        write.writerows(records)


def dis_id():

    rows = db.execute("SELECT stu_id FROM stu")
    header = list(rows[0].keys())
    records = []
    for i in rows:
        records.append(i.values())
    records = list(records)
    with open(file , 'w') as csvfile :
        write = csv.writer(csvfile)
        # write.writerow(header)
        # print(records)
        write.writerows(records)
  

def upt(id, which, new):
    
    try:
        int(id) ; int(new)
    except:
        pass
    db.execute("UPDATE stu SET ? =  ? WHERE stu_id = ? ", which, new , id )


def del_id(id):


    
        try:
            db.execute("INSERT INTO trash SELECT * FROM stu WHERE stu_id = ?", id)
        except:
                pass
        db.execute("DELETE FROM stu WHERE stu_id = ?", id)

def sta():  
    rows = db.execute("SELECT COUNT(*) FROM stu")
    header = list(rows[0].keys())
    records = []
    for i in rows:
        records.append(i.values())
    records = list(records)
    with open(file , 'w') as csvfile :
        write = csv.writer(csvfile)
   
        write.writerows(records)
    for i in ['I', 'M' , 'A', 'R' , 'C']:

        depa =  db.execute("SELECT COUNT(*) FROM stu WHERE depa == ?", i)
        header = list(depa[0].keys())
        records = []
        for i in depa:
            records.append(i.values())
        records = list(records)
        with open(file , 'a') as csvfile :
            write = csv.writer(csvfile)
            write.writerows(records)

       
    
def top():
    rows = db.execute("SElECT * FROM stu ORDER BY GPA  DESC limit 5 ")
    if rows :
        for i in range(len(rows)):
            del   rows[i]["id"]
    header = list(rows[0].keys())
    records = []
    for i in rows :
         records.append(i.values())
    records = list(records)
    with open(file , 'w') as csvfile :
        write = csv.writer(csvfile)
        write.writerows(records)

        records = []
    
