import sys
import re
import json
from pprint import pprint


def loadDatabase():
	studentInfo =list()
	json_data=open("students_test.json")
	data = json.load(json_data)
	return data

def checkID(db, id):
	# print db[]
	# if db["cardID"] == id:
	# 	return 1
	for student in db:
		print student["nyuid"]
		if student["nyuid"] == id:\
			reutrn 1
		else:
			return 0

			 





if __name__ == '__main__':

	data = loadDatabase()
	checkID(data, sys.argv[1])	

