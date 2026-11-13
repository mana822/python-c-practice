# 练习 12.1: 蓝色的天空 
import pygame
import sys
def moban(yuanzu = (0, 0, 200)):
    time = pygame.time.Clock()
    pygame.init()      # 初始化屏幕
    pygame.display.set_caption('蓝色的天空')   # 取名
    scrren = pygame.display.set_mode((1200, 800))    # 都只接受元组，建立屏幕尺寸，只要在外面建立一次就行了
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()             # 要有退出键

        scrren.fill(yuanzu)    # fill直接作用于建立的屏幕
        pygame.display.flip()    # 翻页，没了它，“画了”画面也无法显示
        time.tick(60)

moban()