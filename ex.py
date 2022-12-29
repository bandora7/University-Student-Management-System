from sys import argv
from helpers import *


if argv[1] == "INSERT":
      insert(student_id=int(argv[2]),
              fname=argv[3],
              lname=argv[4],
              depa=argv[5],
              year=argv[6],
              gpa=argv[7])

elif argv[1] == "DISPLAY":
    display(table="stu")

elif argv[1] == "SEARCH":
    display(table="stu", search=True, name=argv[2])

elif argv[1] == "TRASH":
    display(table="trash")

elif argv[1] == "SELECT_ID":
    dis_id()

elif argv[1] == "UPDATE":
    upt(id=int(argv[2]), which=argv[3], new=argv[4])

elif argv[1] == "DEL":
    del_id(id=int(argv[2]))

elif argv[1] == "STA":
    sta()

elif argv[1] == "top":
    top()