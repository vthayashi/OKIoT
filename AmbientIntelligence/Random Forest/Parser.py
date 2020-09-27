import csv

simreport = open("simrep-13.txt","r")
n = 0
states = [["event1", "event2", "event3", "event4", "event5", "event6", "athome", "person"]]
prevevent5 = ""
prevevent4 = ""
prevevent3 = ""
prevevent2 = ""
prevevent = ""
event = ""
prevroom = ""
room = ""
person = ""
athome = ["sister","brother","father","mother"]
athome_state = ""
homedict = {
  "bfms": 1,
  "bfm": 2,
  "bfs": 3,
  "fms": 4,
  "bms": 5,
  "bf": 6,
  "bm": 7,
  "bs": 8,
  "fm": 9,
  "fs": 10,
  "ms": 11,
  "b": 12,
  "f": 13,
  "m": 14,
  "s": 15,
  "": 16
}
persondict = {
  "brother": 1,
  "father": 2,
  "mother": 3,
  "sister": 4
}
eventdict = {
  "RoomC2Hall": 1,
  "RoomG2Hall": 2,
  "RoomB2Hall": 3,
  "Hall2RoomB": 4,
  "Hall2Bath": 5,
  "Hall2Kitchen": 6,
  "Bath2Hall": 7,
  "Kitchen2Storage": 8,
  "Kitchen2LRoom": 9,
  "Storage2Kitchen": 10,
  "LRoom2Kitchen": 11,
  "Kitchen2Hall": 12,
  "Hall2RoomG": 13,
  "Hall2RoomC": 14,
  "LRoom2Laundry": 15,
  "Laundry2Stairs": 16,
  "Stairs2Garage": 17,
  "Garage2Stairs": 18,
  "Stairs2Laundry": 19,
  "Laundry2LRoom": 20,
  "Garage2Out": 21,
  "Out2Garage": 22
}

for line in simreport:

    if (line.find('@') != -1):
        line = line.replace("\n","")
        line = line.replace(" @ (1:home)","")
        line = line[line.rfind("	")+1:]
        prevroom = line[:line.find("2")]
        room = line[line.find("2")+1:]
        #print prevroom
        #print room

    if (line.find('- p') != -1):
        line = line.replace("\n","")
        line = line.replace(" - p = ","")
        line = line.replace("\"","")
        person = line
        #print person

        if room == "Out":
            athome.remove(person)
        if prevroom == "Out":
            athome.append(person)
        athome.sort()
        for state in athome:
            athome_state = athome_state + state[0]

        event = prevroom + "2" + room
        if prevevent5 != "":
            state = [eventdict[prevevent5], eventdict[prevevent4], eventdict[prevevent3],\
                     eventdict[prevevent2], eventdict[prevevent], eventdict[event],\
                     homedict[athome_state], persondict[line]]
        if state != "sister":
            states.append(state)

        athome_state = ""
        prevevent5 = prevevent4
        prevevent4 = prevevent3
        prevevent3 = prevevent2
        prevevent2 = prevevent
        prevevent = event

    n = n + 1

with open('domuscpn.csv', 'wb') as f:

    writer = csv.writer(f)
    
    for state in states:
        writer.writerow(state)
