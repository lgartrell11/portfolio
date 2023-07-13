# Lance Gartrell
# 11/18/22

market_list = open("markets.tsv","r", encoding="ISO-8859-1")
cities_to_zip = {}
zip_to_market = {}

# loop for assigning each markets info to to a respective city and zipcode dictioanry
for market in market_list:

    # split the info in the market tsv at each tab
    individual_info = market.strip().split("\t")
    if len(individual_info) == 7:
        (state, marketname, streetaddress, city, zip_code, longitude, latitude) = individual_info

        # assings the market info to city index for the given city
        if city not in cities_to_zip:
            cities_to_zip[city] = [(state, marketname, streetaddress, city, zip_code, longitude, latitude)]
        else: 
            cities_to_zip[city].append((state, marketname, streetaddress, city, zip_code, longitude, latitude)) 

        # assings the market info to zip index for the given index    
        if zip_code not in zip_to_market:
            zip_to_market[zip_code] = [(state, marketname, streetaddress, city, zip_code, longitude, latitude)]
        else: 
            zip_to_market[zip_code].append((state, marketname, streetaddress, city, zip_code, longitude, latitude))

print("Please enter a city or zipcode:")
input_city_or_zipcode = input()

# loop for continually asking user for city/zip input
while input_city_or_zipcode != "quit":
    info = (state, marketname, streetaddress, city, zip_code, longitude, latitude)

    # print the markets in the inputed city
    if input_city_or_zipcode in cities_to_zip:
        for (state, marketname, streetaddress, city, zip_code, longitude, latitude) in cities_to_zip[input_city_or_zipcode]:
            print(state, marketname, streetaddress, city, zip_code, longitude, latitude)

    # print the markets in the inputed zip code
    elif input_city_or_zipcode in zip_to_market:
        for (state, marketname, streetaddress, city, zip_code, longitude, latitude) in zip_to_market[input_city_or_zipcode]:
            print(state, marketname, streetaddress, city, zip_code, longitude, latitude)
    else:
         print("Cannot find any markets in that area") 
    print("please enter a city or zip code")
    input_city_or_zipcode = input()

print("Bye")


    