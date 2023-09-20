import json

result = []

with open("bike.json", encoding='utf8') as file:
    data = json.load(file)
    for item in data:
        if int(item['sbi']) >= 5:
            result.append(item)

result.sort(key=lambda x: int(x['sbi']))

for item in result:
    print(f'{item["sno"]:5s}{item["sna"]:15s}{item["tot"]:5s}{item["sbi"]:5s}{item["ar"]:15s}{item["bemp"]:5s}')
