import PIL
import PIL.Image
import PIL.ImageDraw
import PIL.ImageFont
from math import pi

BALL_R = 200
TEXT_CRC_R = 100
IMAGE_WIDTH = int(BALL_R*2*pi)
IMAGE_HEIGHT = int(BALL_R*pi)
SPRITE_START = 0.3
FONT = PIL.ImageFont.truetype(r'C:\Users\System-Pc\Desktop\arial.ttf', TEXT_CRC_R+80)
COLORS = ['yellow', 'blue', 'red', 'purple', 'orange', 'green', 'cyan']

def ball_type1(text, color):
    image = PIL.Image.new('RGB', (IMAGE_WIDTH, IMAGE_HEIGHT))
    image_draw = PIL.ImageDraw.Draw(image)
    image_draw.rectangle(((0,0), (IMAGE_WIDTH, IMAGE_HEIGHT)), color, None)
    image_draw.ellipse(((IMAGE_WIDTH/2-TEXT_CRC_R, IMAGE_HEIGHT/2-TEXT_CRC_R), (IMAGE_WIDTH/2+TEXT_CRC_R, IMAGE_HEIGHT/2+TEXT_CRC_R)), 'white')
    bbox = FONT.getbbox(text)
    size = (bbox[2], bbox[3])
    image_draw.text((IMAGE_WIDTH/2-size[0]/2, IMAGE_HEIGHT/2-size[1]/2-10), text, 'black', FONT)
    return image

def ball_type2(text, color):
    image = PIL.Image.new('RGB', (IMAGE_WIDTH, IMAGE_HEIGHT))
    image_draw = PIL.ImageDraw.Draw(image)
    image_draw.rectangle(((0,0), (IMAGE_WIDTH, IMAGE_HEIGHT)), 'white', None)
    STRIPE_TOP = SPRITE_START*IMAGE_HEIGHT
    STRIPE_BOTTOM = IMAGE_HEIGHT-STRIPE_TOP
    image_draw.rectangle(((0,STRIPE_TOP), (IMAGE_WIDTH, STRIPE_BOTTOM)), color, None)
    image_draw.ellipse(((IMAGE_WIDTH/2-TEXT_CRC_R, IMAGE_HEIGHT/2-TEXT_CRC_R), (IMAGE_WIDTH/2+TEXT_CRC_R, IMAGE_HEIGHT/2+TEXT_CRC_R)), 'white')
    bbox = FONT.getbbox(text)
    size = (bbox[2], bbox[3])
    image_draw.text((IMAGE_WIDTH/2-size[0]/2, IMAGE_HEIGHT/2-size[1]/2-10), text, 'black', FONT)
    
    return image

def generate():
    for i,color in enumerate(COLORS):
        # color = 'blue'
        # text = '5'
        text = str(i+1)
        ball_type1(text,color).save(f'assets/ballA{i}.jpg')
        ball_type2(text,color).save(f'assets/ballB{i}.jpg')
    
    ball_type1('8', 'black').save('assets/ballA7.jpg')

generate()
