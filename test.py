import pandas
from math import log2


# 計算 entropy
def calcute_entropy(data: pandas.DataFrame, labels: dict, attribute: str):
    entropy = 0
    # 遍歷所有的 label
    for label in labels[attribute]:
        # 計算label出現機率
        probability = len(data[data[attribute] == label]) / len(data)
        # 如果機率為 0，跳過entropy的計算(因為在log2(0)沒有定義，且0*log2(0) = 0) (**幫我檢查這裡寫的484對的**)
        if probability == 0:
            continue
        # 計算 entropy
        entropy += -probability * log2(probability)
    return entropy


# 計算 information gain
def calcute_information_gain(
    data: pandas.DataFrame, labels: dict, attribute: str, column: str
):
    gain = calcute_entropy(data, labels, attribute)
    for label in labels[column]:
        sub_data = data[data[column] == label]
        gain -= len(sub_data) / len(data) * calcute_entropy(sub_data, labels, attribute)
    return gain


def main():
    # 將原始資料寫入程式，用dictionary方式儲存
    raw_data = {
        "Outlook": [
            "Sunny",
            "Sunny",
            "Overcast",
            "Rain",
            "Rain",
            "Rain",
            "Overcast",
            "Sunny",
            "Sunny",
            "Rain",
        ],
        "Temperature": [
            "Hot",
            "Hot",
            "Hot",
            "Mild",
            "Cool",
            "Cool",
            "Cool",
            "Mild",
            "Cool",
            "Mild",
        ],
        "Humidity": [
            "High",
            "High",
            "High",
            "High",
            "Normal",
            "Normal",
            "Normal",
            "High",
            "Normal",
            "Normal",
        ],
        "Wind": [
            "Weak",
            "Strong",
            "Weak",
            "Weak",
            "Weak",
            "Strong",
            "Weak",
            "Weak",
            "Weak",
            "Strong",
        ],
        "Play Tennis": [
            "No",
            "No",
            "Yes",
            "Yes",
            "Yes",
            "No",
            "Yes",
            "No",
            "Yes",
            "Yes",
        ],
    }

    # 將原始資料的標籤寫入程式，用dictionary方式儲存
    labels = {
        "Outlook": ["Sunny", "Overcast", "Rain"],
        "Temperature": ["Hot", "Mild", "Cool"],
        "Humidity": ["High", "Normal"],
        "Wind": ["Weak", "Strong"],
        "Play Tennis": ["No", "Yes"],
    }

    columns = ["Outlook", "Temperature", "Humidity", "Wind"]

    # 將原始資料轉換成pandas.DataFrame，index為天數
    tennis_data = pandas.DataFrame(
        raw_data, index=["D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10"]
    )

    # 計算第一層
    best_gain = 0
    root_node = ""
    for column in columns:
        if calcute_information_gain(tennis_data, labels, "Play Tennis", column) > best_gain:
            best_gain = calcute_information_gain(tennis_data, labels, "Play Tennis", column)
            root_node = column
    print(root_node)

    # 計算第二層第一個節點 (假設向下的邊為Sunny)
    columns.remove(root_node)
    best_gain = 0
    node = ""
    for column in columns:
        if calcute_information_gain(tennis_data[tennis_data[root_node] == "Sunny"], labels, "Play Tennis", column) > best_gain:
            best_gain = calcute_information_gain(tennis_data[tennis_data[root_node] == "Sunny"], labels, "Play Tennis", column)
            node = column
    print(node)



    # test (殼已無視這裡的程式碼)
    # print(tennis_data)
    # print(tennis_data[tennis_data["Play Tennis"] == "Yes"])
    # print(calcute_entropy(tennis_data, labels, "Play Tennis"))
    # print(calcute_information_gain(tennis_data, labels, "Play Tennis", "Temperature"))
    # print(calcute_information_gain(tennis_data, labels, "Play Tennis", "Humidity"))
    # print(calcute_information_gain(tennis_data, labels, "Play Tennis", "Wind"))
    # print(calcute_information_gain(tennis_data, labels, "Play Tennis", "Outlook"))


if __name__ == "__main__":
    main()