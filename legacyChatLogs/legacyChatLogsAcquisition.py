import datetime
import os
import re
import urllib.request

ROOMS = ["Fr", "Ru", "World"]

START_DATE = datetime.datetime(2020, 3, 8)
END_DATE = datetime.datetime(2022, 7, 14)

MESSAGE_REGEX = re.compile("(?:<p>(?:<a.*?>)?<img.*?>(?:</a>)?(.*?:.*?)</p>)|(?:<p>.*?</p>)")

for room in ROOMS:

    folder = "legacyChatLogs/{}".format(room)

    try: os.mkdir(folder)
    except: pass

    date = START_DATE

    while date <= END_DATE:

        stringDate = date.strftime("%Y-%m-%d")

        url = "https://cg.spdns.eu/wiki/Chat:{}/{}".format(room, stringDate)

        try:

            page = urllib.request.urlopen(url).read().decode('utf-8').replace("\n", "")

            results = MESSAGE_REGEX.findall(page)

            print("Saving the {} logs of the {} room...".format(stringDate, room))

            if len(results) > 0:

                file = open("{}/{}".format(folder, stringDate), "w")

                for result in results:
                    
                    if result != "":
                        
                        file.write("{}\n".format(result))
        
        except: pass

        date += datetime.timedelta(days=1)