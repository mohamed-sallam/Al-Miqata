***[Click for English](#al-miqata-)***

# الميقاتة ⏰🕌 
الميقاتة هي ساعة حائط إسلامية رقمية مصممة لمساعدة المسلم في معرفة أوقات الصلاة. بفضل مجموعة متنوعة من الميزات، تهدف الميقاتة إلى التيسير على المسلمين مع الحفاظ على التكلفة المعقولة.

> ألا إنني للدين خير أداةِ *** إذا غاب عنكم وقتُ كل صلاةِ  
> ولم تُرَ شمسٌ بالنهار ولم تُنَر  *** كواكبُ ليلٍ حالِكِ الظُلمات  
> بيُمن إمام المرسلين محمّدٍ  *** تجلّت عن الأوقاتِ كلُّ صلاةِ  
> — منقول بتصرف طفيف عن [عباس بن فرناس](https://www.aldiwan.net/poem68990.html)

![34](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/3146b852-d663-4ef0-b840-6c5cbcce4c6f)


## مميزات ✨
✅ رخيص 💰  
✅ عرض أوقات الصلاة الخمس مع وقت الشروق. 🌅  
✅ عرض التاريخ الهجري والميلادي. 🗓️  
✅ عرض الوقت بكل من التنسيقين الـ 24 ساعة والـ 12 ساعة. ⏰  
✅ عرض يوم الأسبوع الحالي. 📅  
✅ الحفاظ على إعدادات الوقت في حالة انقطاع الطاقة. 💡  
 🚧 يحسب الوقت المتبقي على إقامة الصلاة التالية. ⏳  
 ❌ يمكّن من معايرة الإعدادات (التاريخ، الوقت، الموقع، وما إلى ذلك) عبر تطبيق للأجهزة المحمول باستخدام الواي فاي. 📱🌐  


# Al-Miqata ⏰🕌
Al-Miqata is a digital Islamic wall clock designed to assist Muslims in managing their daily prayers effectively. With its array of features, Al-Miqata aims to provide convenience and utility to its users while maintaining affordability.
> Behold, I am the finest aid to faith's decree,  
> When each prayer's appointed hour you fail to see.  
> When neither sun illuminates the day's course,  
> Nor stars in the night sky offer guiding force.  
> By the grace of the Messenger, Muhammad, so true,  
> Each prayer's time revealed, clear and anew.  
> — ChatGPT's translation of a slightly altered Arabic version, [originally by Abbas ibn Firnas](https://www.aldiwan.net/poem68990.html)


![34](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/3146b852-d663-4ef0-b840-6c5cbcce4c6f)


## Features ✨
- [x] Cost-effective 💰
  - [ ] Use more cheaper MCU   
- [x] Displays five daily prayer times along with the sunrise time. 🌅
- [x] Presents the date in both Hijri and Gregorian calendars. 🗓️
- [x] Displays time in both 24-hour and 12-hour formats. ⏰
- [x] Indicates the current day of the week. 📅
- [x] Implements a method to preserve time settings in case of power loss. 💡
- [ ] 🚧 Provides the remaining time until the Iqama for the upcoming prayer. ⏳
- [ ] Enables calibration of settings (date, time, location, ...etc.) through a mobile application using WIFI connectivity. 📱🌐

# Build and Run 🚀
1. Install [PlatformIO extension for VSCode](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).
  > [!TIP]
  > If you are using Ubuntu-based distro, it mightn't be able to identify Python path read [this](https://community.platformio.org/t/ubuntu-vscode-pio-extension-install-platformio-can-not-find-working-python-3-6-interpreter/27853/9).
2. Open PlatformIO tab from VSCode Activity Bar.
3. Wait until the project is detected by PlatformIO.
![20](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/5c2f91f8-7fcb-4726-abfe-a549dd2ff82c)
![1](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/aa6393d7-e774-4a00-aa89-ef27e44211b3)
![13](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/6bad3a5a-8826-42d0-b108-ef8d6d4ba7a7)
4. Click "Build" button under "ATmega328P > General".
![41](https://github.com/mohamed-sallam/Al-Miqata/assets/59128458/89b02588-954e-47b8-88b8-19c8ec44a84c)
5. It should give you success message such as:
   ```
   ================ [SUCCESS] Took 0.88 seconds ================
   ```
   and create `.pio/build/ATmega328P/firmware.hex` file.
6. Burn `.pio/build/ATmega328P/firmware.hex` file into your MCU or if you're using Proteus 8.9 or later, open `al-miqata_schematic.pdsprj` in Proteus and then double click on the ATmega328P MCU on the schematic and in "Program File:" field browse to `.pio/build/ATmega328P/firmware.hex`.
