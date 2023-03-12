from PIL import Image, ImageDraw, ImageFont
import turtle


def bigPoint(coord, color):
    for pos in coord:
        draw.ellipse((pos[0]-1,pos[1]-1,pos[0]+1,pos[1]+1), color)
        fnt = ImageFont.truetype("Pillow/Tests/fonts/FreeMono.ttf", 8)
        draw.text((pos[0]+2,pos[1]+2), str(int(pos[0]))+ ',' + str(int(pos[1])), font=fnt, fill=color)


def connect(point1, point2, k):
    draw.line([(point1[0],point1[1]),(point2[0],point2[1])], 'blue', 1)
    x = point1[0] + (point2[0]-point1[0])*k
    y = point1[1] + (point2[1]-point1[1])*k
    bigPoint([(x,y)], 'yellow')
    return (x,y)


def bezier(points, color):
    order = len(points)
    if order <= 0:
        return 0
    print(order)
    bigPoint(points, 'cyan')
    new_points = []
    for i in range(0, order):
        if i != order-1:
            new_point = connect(points[i], points[i+1], 0.4)
            new_points.append(new_point)
    bezier(new_points,color)


im = Image.new('RGB', (500, 400), 'black')
draw = ImageDraw.Draw(im)
#draw.point([(100,100), (100, 200), (200, 100), (200, 200)], 'red')
#draw.line([(100,100), (100, 200), (200, 100), (200, 200)], 'green', 1)
#draw.ellipse((300,300,302,302), 'cyan')
#bigPoint([(100,100), (100, 200), (200, 100), (200, 200)], 'cyan')
bezier([(100,100), (100, 200), (200, 100), (200, 200), (300,250)], 'red')

fnt = ImageFont.truetype("Pillow/Tests/fonts/FreeMono.ttf", 10)
# draw text, half opacity
draw.text((0,0), "Hello", font=fnt, fill=(255,255,255,128))
# draw text, full opacity
draw.text((10,60), "World", font=fnt, fill=(255,255,255,255))


x1 = 400
y1 = 300

x2 = 350
y2 = 200

#bigPoint([(x1,y1), (x2,y2)], 'white')
#draw.line([(x1,y1), (x2,y2)], 'red')

#bigPoint([(x1+(x2-x1)*0.2,y1+(y2-y1)*0.2)], 'white')

connect((x1,y1), (x2,y2), 0.3)


im.save('testimg.jpg', quality = 95)