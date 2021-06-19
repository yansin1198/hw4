# hw4

# PART1 XBee Controlled BBCar
	
	1.首先使用XBee傳送RPC command給BBCar，當BBCar接收到command後將會呼叫RPCfunction。
	2.根據傳送的command中，W/E用以表示車子目前面向的方位，接著使用d1、d2去計算退後的距離，過程中也會根據W/E去判斷BBCar應當向左還是向右轉，而後完成停車。
	
## Demo Video
	
	1. d1 = 7 d2 = 7 west 
https://drive.google.com/file/d/1mYddQ2ckLGtR7JZaUHPfftnPOUKFuO1x/view?usp=sharing
	
	2. d1 = 12 d2 = 4 east
https://drive.google.com/file/d/1mWv7AzzpKJVUxq1ZJzd-QgRyLilpwYO9/view?usp=sharing
	
	3. d1 = 11 d2 = 9 east
https://drive.google.com/file/d/1mam6KdGrpApy-d884KJI1CP7itcaClyv/view?usp=sharing

# PART2 Line Following BB Car
	
	基於Lab14的4.7 Line Detection加以延伸，增加判斷目標直線的條件，而避免偵測環境中其他非目標的線段。
	
## Demo Video
	
	影片中可注意筆電畫面的右上方，會看到目標線段出現在openMV的視角範圍，並且BBCar會沿著線段前進，當線段不再出現於openMV視角內，BBCar將會停止前進。
https://drive.google.com/file/d/1me8nJvVraLZ-uMa4XLnaBG2tl2rFcxIl/view?usp=sharing

# PART3 BBCar_Position_Calibration

	因為openMV壞掉，因此這題改成利用PING辨識特殊幾何形狀物件。
	
## Demo Video

https://drive.google.com/file/d/1ocD8ynPtgJZS6EpeO7osdYNAmKvTmgvt/view?usp=sharing
