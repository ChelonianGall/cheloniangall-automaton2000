"""
    cheloniangall.com is a website created to host a webchat intended to replace the CodinGame's deleted one.
    Copyright (C) 2022 BlaiseEbuth
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

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