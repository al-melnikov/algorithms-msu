from PIL import Image, ImageDraw, ImageFont
import numpy as np
import random


def bigPoint(coord, color):
    for pos in coord:
        draw.ellipse((pos[0]-1,pos[1]-1,pos[0]+1,pos[1]+1), color)
        fnt = ImageFont.truetype("Pillow/Tests/fonts/FreeMono.ttf", 8)
        draw.text((pos[0]+2,pos[1]+2), str(int(pos[0]))+ ',' + str(int(pos[1])), font=fnt, fill=color)
        



def connect(point1, point2, k):
    #draw.line([(point1[0],point1[1]),(point2[0],point2[1])], 'blue', 1)
    x = point1[0] + (point2[0]-point1[0])*k
    y = point1[1] + (point2[1]-point1[1])*k
    #bigPoint([(x,y)], 'yellow')
    return (x,y)

def lines(points, color):
    for i in range (0, len(points)-1):
        draw.line([(points[i][0],points[i][1]),(points[i+1][0],points[i+1][1])], color)


def bezierPoint(points, k, color):
    if len(points) == 2:
        x = points[0][0] + (points[1][0]-points[0][0])*k
        y = points[0][1] + (points[1][1]-points[0][1])*k 
        draw.point([(x, y)], color)
        return
    order = len(points)
    new_points = []
    for i in range(0, order):
        if i != order-1:
            new_point = connect(points[i], points[i+1], k)
            new_points.append(new_point)
    bezierPoint(new_points, k, color)


def bezier(points, color):
    bigPoint(points, 'cyan')
    lines(points, 'grey')
    for k in np.arange(0, 1, 0.001):
        bezierPoint(points, k, color)



MAX_POINTS_NUMBER = 10
IMG_TO_GENERATE = 3
WIDTH = 600
HEIGHT = 400


def main():
    for order in range (3, MAX_POINTS_NUMBER+1):
        for time in range(0, IMG_TO_GENERATE):
            points = []
            for i in range(order):
                x = random.randrange(50, WIDTH-50)
                y = random.randrange(50, HEIGHT-50)
                point = (x,y)
                points.append(point)
            im = Image.new('RGB', (WIDTH, HEIGHT), 'black')
            global draw 
            draw = ImageDraw.Draw(im)
            bezier(points, 'red')
            name = 'bez_' + str(order) + '_' + str(time) + '.jpg'
            im.save(name, quality = 95)

im = Image.new('RGB', (WIDTH, HEIGHT), 'black')
draw = ImageDraw.Draw(im)
points = [(100,100), (300,100), (100,300), (300,300)]    
bezier(points, 'red')
name = 'z-letter.jpg'
im.save(name, quality = 95)

#if __name__ == '__main__':
#    main()


