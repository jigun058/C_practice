def monthsLater(m, r, deposit, asset):
    if(m == 0):
        return asset
    
    asset += deposit
    asset *= 1 + r/100
    return monthsLater(m-1, r, deposit, asset)

def yearsLater(y, r, deposit, asset):
    if(y == 0):
        return asset
    
    asset += deposit
    asset *= 1 + r/100
    return yearsLater(y-1, r, deposit, asset)
    
a = input("1 : 월 이자 계산\n2 : 연 이자 계산\n-> ")

if a == "1":
    print("m개월 동안, 매 월 r%의 이자로, d원만큼 매 달 저축하기, 초기 자금 a원(첫 월 저축 전)\nm r d a : ", end = "")
    m, r, d, a = map(int, input().split())

    print(m, "개월 뒤 자산 : ", int(monthsLater(m, r, d, a)), "원")

elif a == "2":
    print("y년 동안, 매 년 r%의 이자로, d원만큼 매 해 저축하기, 초기 자금 a원(첫 연도 저축 전)\ny r d a : ", end = "")
    y, r, d, a = map(int, input().split())

    print(y, "년 뒤 자산 : ", int(yearsLater(y, r, d, a)), "원")