# 练习 12.2 游戏角色
import sys
import pygame


class Weibaozi:
    def __init__(self):
        
        pygame.init()
        self.screen = pygame.display.set_mode((1200, 1000))
        self.time = pygame.time.Clock()
        self.name = pygame.display.set_caption('维多利加')  # set_caption返回空，没意义
    def run_up(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
            
            self.screen.fill((255, 255, 0))   # fill冲刷背景
            self.images()          
            pygame.display.flip()   # 翻页
            self.time.tick(60)  # 图片这个没必要

    def images(self):
        self.screen_rect = self.screen.get_rect()
        self.image = pygame.image.load('lianxi/image/wei.bmp')
        self.rect = self.image.get_rect()
        self.rect.center = self.screen_rect.center
        self.screen.blit(self.image, self.rect)

wi = Weibaozi()
wi.run_up()



# 练习 12.2 里 class Weibaozi 的 run_up 方法里 self.images() 每次循环都重新加载图片，
# 且 self.screen_rect、self.image、self.rect 每次循环都重新计算，应该把不变的部分放到 __init__。