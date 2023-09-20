import csv

pos = list(map(int, input("經緯度(整數): ").split(' ')))
offset1 = int(input("經度偏離值 "))
offset2 = int(input("緯度偏離值 "))
i = 0
result = []

with open('pmi.csv', 'r', encoding='utf-8') as f:
    plots = csv.reader(f, delimiter=",")
    for row in plots:
        if i == 0:
            i += 1
            continue
        if pos[0]-offset1<float(row[4])<pos[0]+offset1 and pos[1]-offset2<float(row[5])<pos[1]+offset2:
            result.append((row[0], row[2]))

result.sort(key=lambda x: float(x[1]))
for item in result:
    print(item[0], item[1])