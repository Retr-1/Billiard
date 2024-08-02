import PIL
import PIL.Image
import PIL.ImageDraw
import PIL.ImageFont

BALL_R = 400
TEXT_CRC_R = 100
FONT = PIL.ImageFont.truetype(r'C:\Users\System-Pc\Desktop\arial.ttf', 100)
COLORS = ['yellow', 'blue', 'red', 'purple', 'orange', 'green', 'cyan']

def ball_type1(text, color):
    image = PIL.Image.new('RGB', (BALL_R*2, BALL_R))
    image_draw = PIL.ImageDraw.Draw(image)
    image_draw.rectangle(((0,0), (BALL_R*2, BALL_R)), color, None)
    image_draw.ellipse(((BALL_R-TEXT_CRC_R, BALL_R/2-TEXT_CRC_R), (BALL_R+TEXT_CRC_R, BALL_R/2+TEXT_CRC_R)), 'white')
    FONT = PIL.ImageFont.truetype(r'C:\Users\System-Pc\Desktop\arial.ttf', 100)
    # bbox = image_draw.textbbox((BALL_R,BALL_R/2), text, FONT)  
    bbox = FONT.getbbox(text)
    size = (bbox[2], bbox[3])
    # print(size)
    image_draw.text((BALL_R-size[0]/2, BALL_R/2-size[1]/2-10), text, 'black', FONT)
    # image.show()
    return image

def ball_type2(text, color):
    image = PIL.Image.new('RGB', (BALL_R*2, BALL_R))
    image_draw = PIL.ImageDraw.Draw(image)
    image_draw.rectangle(((0,0), (BALL_R*2, BALL_R)), 'white', None)
    STRIPE_TOP = 0.2*BALL_R
    STRIPE_BOTTOM = BALL_R-STRIPE_TOP
    image_draw.rectangle(((0,STRIPE_TOP), (BALL_R*2, STRIPE_BOTTOM)), color, None)
    image_draw.ellipse(((BALL_R-TEXT_CRC_R, BALL_R/2-TEXT_CRC_R), (BALL_R+TEXT_CRC_R, BALL_R/2+TEXT_CRC_R)), 'white')

    # bbox = image_draw.textbbox((BALL_R,BALL_R/2), text, FONT)  
    bbox = FONT.getbbox(text)
    size = (bbox[2], bbox[3])
    # print(size)
    image_draw.text((BALL_R-size[0]/2, BALL_R/2-size[1]/2-10), text, 'black', FONT)
    
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
