# Spaceinvader_HCRL_M5Stack
ตัวโค้ดหลักคือ test_spaceinvader.ino นอกเหนือจากนี้เป็นรูปภาพที่ convert เป็น c array
การ dev เกมครั้งนี้ใช้ platform Arduino ทั้งหมด
หากตั้งการจำนำโค้ดไปใช้ต้องทำการติดตั้ง library เพิ่มเติมดังนี้                                                                                                                               
 1.M5stack master : https://github.com/m5stack/M5Stack                                                                                                                           
 2.Lvgl master : https://github.com/lvgl/lv_arduino
 
โค้ดผมอาจจะขยะหน่อยนะครับ ผมไม่เคยเขียนเกมมาก่อน ศึกษาเรียนรู้ด้วยตัวเองหมดครับ 😂😂

//=================================================================================================================
 - ตัวรูปภาพนำรูปจาก google นำมา photoshop ปรับขนาดให้มี pixel = หน้าจอของตัว M5.Lcd
 
 - โดยการแปลงไฟล์จาก png ให้เป็น C array โดยใช้เว็บไซต์ https://lvgl.io/tools/imageconverter
 
 - ในการใช้งาน lvgl จำเป็นต้องดาวน์โหลด library เพิ่มเติมจาก https://github.com/lvgl/lv_arduino เพื่อเรียกใช้งาน header Lvgl.h
 
 - ตัวพื้นหลัง 3 มิติผมนำมาจาก Example library ของ M5stack ชื่อ TFT_starchart https://github.com/m5stack/M5Stack/tree/master/examples/Advanced/Display/TFT_Starfield
   เวลาภายในเกมผมพยายามไม่ใช้ delay(); แต่จะพยายามใช้ millis(); เพื่อไม่ให้การทำงานกระทบกัน
   
 - ในโค้ดผมไม่ได้ใช้งาน oob เลยอาจจะเข้าใจโค้ดผมยากหน่อยนะครับ ( บางทีผมประกาศตัวแปรชื่อแปลกๆก็ขออภัยนะครับ )
 
In game opton:
 -ความเร็วเอเลี่ยน = ปรับแต่งได้ที่ตัวแปร speedalien = (ความเร็วของเอเลี่ยนคือเคลื่อนที่ทีละ 5 ช่อง)
 -การเพิ่มความเร็วของเอเลี่ยนหลังจบแต่ละเลเวลปรับได้ที่ function levelup(); ที่คำว่า speedalien += 3
 -เหตุผลที่เมื่อเลเวลสูงๆแล้วเอเลี่ยนเหมือนวาปๆเป็นเพราะ speedalien มันเพิ่มขึ้นมากเกินไป (สมมุติเคลื่อนที่แค่ 1 ครั้งแต่ไปทีละ 15 ช่อง ก็จเห็นว่ามันวาปๆ)
 -ที่ผมไม่นำ millis(); มาใช้กับความเร็วของ alien เป็นเพราะผมลองดูแล้วเหมือนเครื่อง m5 มันรับไม่ไหว เครื่องมันหน่วงๆไปหมดเหมือนระบบประมวลผลไม่ทัน เลยเลือกใช้ให้เพิ่มช่องในการเคลื่อนที่แทน
 -สำหรับผมสิ่งที่ยากที่สุดในการทำเกมนี้คือการทำระบบการยิงครับ ปวดหัวมากๆ แก้บัค 3 วัน 😂😂 ที่เห็นว่ามันยิงแบบฟูลออโต้ได้เพราะผมทำตัวแปรสำหรับกระสุนไว้ 4 อันเมื่อกระสุนออกจากหน้าจอแล้วให้มันรีเซ็ทกระสุนใหม่ จึงทำให้     เหมือนยิงออโต้ แต่ถ้าหากลองปรับให้ความเร็วกระสุนเหลือน้อยๆจะพบว่ามันก็ยิงออกมาได้แค่ 4 นัดแหละครับ พอกระสุนแรกที่ยิงออกไปออกไปเกินของเขตหน้าจอก็ให้มันรีเซ็ทใหม่
 
How I dev this game ??
- เริ่มด้วยการทำระบบการเคลื่อนที่ก่อนเลยครับ M5.BtnA.wasPressed (syntax) 

- ตอนแรกผมกะจะเล่นใหญ่คือระหว่างเล่นก็จมีพื้นหลัง TFT_starchart ด้วยแต่พอนำมาใส่ปุ้บ เหมือนเครื่องมันรับไม่ไหว โคตรหน่วงไปหมด (เนื่องจากพื้นหลัง starchart เป็นการ random จุด pixel แล้วให้มันมีการเคลื่อนที่เปนทิศ   แบบสุ่ม ซึ่งแม่งแสดงออกมาทีเป็นพันๆ pixel เคลื่อนที่แบบสุ่ม จึงเป็นสาเหตุของการแลคครับ) จึงตัดสินใจนำออกไปแล้วเอาไปใส่เป็นลูกเล่นเวลา levelup แทน

- หลังจากนั้นก็ออกแบบระบบการยิง(ติดบัคเป็นล้าน)ส่วนมากบัคที่พบคือเมื่อยิงกระสุนแรกออกและกดยิงกระสุนนัดที่ 2 แล้วกระสุนแรกมันจะค้างอยู่กับที่ ผมจึงต้องสร้างตัวแปล read กับ shoot เพื่อควบคุมการยิง

- ต่อมาก็ออกแบบ alien โดยออกแบบให้ alien มี 18 ตัว (6*3) ด้วยการใช้ for loop C<18; C++; และและออกแบบ fuction สำหรับตำแหน่ง x และ y ของ alien ใช้ bool numalien[18] ไว้เช็คว่าเอเลี่ยนตัวนั้นตายหรือยัง

- หลังจากนั้นก็ออกแบบ function ชื่อ gotshot ไว้เช็คเมื่อกระสุนชนกับ alien ถ้าหากชนให้ numalien[ตัวที่ถูกยิง] เป็น false และใช้ M5.Lcd.filRect เพื่อวาดสี่เหลี่ยม มาทับรูปเอเลี่ยนตัวนั้น 
(อย่าเผลอใช้ M5.Lcd.drawRect ผมหาบัคนานมากเพราะเผลอใส่ผิด 😂😂 ) 
ขอแค่ได้ส่วนนี้เกมก็เริ่มเป็รเกมแล้วครับ ส่วนที่เหลือก็ง่ายๆแล้ว

- หลังจากนี้ผมออกแบบหน้าจอก่อนเริ่มเกม ให้ยังไม่เริ่มเกมจนกว่าจะกด BtnB (button B) ด้วยการสร้างตัวแปรชื่อ play ขึ้นมาอีกตัวเพื่อหยุดการทำงานอื่นๆทั้งหมด

- ต่อมาก็ออกแบบการ gameover เมื่อ alien ชนยานหรือ alien ชนกับขอบล่างสุดของจอ เมื่อ gameover การทำงานทุกอย่างจะถูกหยุดด้วยให้ play=false

- เสร็จแล้วผมก็ออกแบบการ levelup เมื่อ countalien == 0 เมื่อไหร่ให้เข้าฟังก์ชั่น levelup ในระหว่งเข้าฟังก์ชั่น level up จะทำการรีเซ็ทค่า alien ให้กลับมามีชีวิตใหม่ 
  โดยผมใส่ลูกเล่นการ level up ด้วยการให้ยานบินขึ้นไปสุดจอ + การใช้พื้นหลังขยับด้วย TFT_Starchart เพื่อความสวยงามและโคตรจ๊าบของผม
  
- ตอนนี้รูปเกมของผมก็ถือได้ว่าสมบูรณ์แล้วแหละครับ แต่พอลองเล่นแล้วมันเหมือนขาดอะไๆรบางอย่างผมเลยใส่ ตัวนับ score ให้ด้วยเมื่อยิงโดน score++ และผมก็ใส่เวลาเข้าไปด้วยให้นับเป็นแบบวินาทีด้วย time=millis()/1000
  ตอนแรกกะจะทำ scoreboard สูงสุดด้วย แต่คิดไปคิดมาก็น่าจะยากอยู่นะครับเพราะเวลา gameover เราต้องรีเซ็ท device ใหม่พวก score ก็จะหายไป เว้นแต่ผมใช้ cloud ซึ่งน่าจะต้องใช้ wifi แหละครับ


จบเท่านี้แหละครับการ dev เกมครั้งแรกของผม ใช้เวลาทั้งหมด 2 อาทิตย์เต็มนอนตี 4 มาสองคืน 55555 
ขอบคุณพี่แลป hcrl ที่ทำให้ผมหัดรู้จักต้องพยายามหาความรู้ที่ผมไม่มีพื้นฐานมาก่อนเองสะบ้าง 😂😂 ผมสนุกกับการทำมากครับ แต่บางทีก็หัวร้อนมากๆตอนแก้บัค


 
