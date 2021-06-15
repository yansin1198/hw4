import pyb, sensor, image, time, math

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)

THRESHOLD = (0, 100)
BINARY_VISIBLE = True
enable_lens_corr = False

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()

detectLine = 0
stop = 0

while(True):
    clock.tick()
    img = sensor.snapshot()
    if enable_lens_corr: img.lens_corr(1.8) # for 2.8mm lens...

    for l in img.find_line_segments(merge_distance = 0, max_theta_diff = 5):
        #if l.magnitude() > 3:
        if l.y2() == 0 & stop == 0:
            print(l)
            img.draw_line(l.line(), color = (255, 0, 0))
            detectLine = 1
            uart.write(("%d" % detectLine).encode())
            print("detectLine = %d" % detectLine)
            if l.length() <= 11 :
                #print(l)
                detectLine = 0
                stop = 1
                img.draw_line(l.line(), color = (0, 255, 0))
                uart.write(("%d" % detectLine).encode())
                print("detectLine = %d" % detectLine)



    time.sleep(1)

