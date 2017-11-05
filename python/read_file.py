import csv

FILE = 'example'

# Parse references
if FILE != "NULL":
    print "Trying to get references from \'" + FILE + "\'... \n",
    try:
        with open(FILE) as f:
            parsed_ref = [line.rstrip('\n') for line in open(FILE)]
        #print "Got \'em."
    except:
        print "Nope, ignoring references."


reader = csv.reader(parsed_ref, delimiter=';')

for r in reader:

    print float(r[0])
    print float(r[1])
    print float(r[2])
    print float(r[3])
    print float(r[4])
