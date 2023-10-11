import requests

url = 'https://data.ntpc.gov.tw/api/datasets/54a507c4-c038-41b5-bf60-bbecb9d052c6/json/preview'

response = requests.get(url)


if response.status_code == 200:
    print(f'{"ROAD":10s} {"DAY":5s} {"HOUR":20s}')
    data = response.json()
    filtered_data = []
    for item in data:
        if item['CELLSTATUS'] == 'Y' and item['PAY'] == '計時收費':
            filtered_data.append(item)
            if len(filtered_data) == 5:
                break
    for item in filtered_data:
        print(f"{item['ROADNAME']:10s} {item['DAY']:5s} {item['HOUR']:20s}")
else:
    print('Failed to retrieve data from API')
