import pygame

class Ship:
    """管理飞船的类"""
    def __init__(self, ai_game):  # 除了self引用，还有一个指向当前AlienInvasion实例的引用。
        """初始化飞船并设置其初始位置"""
        self.screen = ai_game.screen   # 将屏幕赋值给一个属性可以方便访问
        self.screen_rect = ai_game.screen.get_rect() # 使用get_rect()方法访问屏幕的rect属性，并将其赋值给self.screen_rect，这让我们能将飞船放到正确位置

        # 加载飞船图像并获取其外接矩形
        self.image = pygame.image.load('xiangmu/alien_invasion/images/ship.bmp')  # 用这个方法传递图像，这时将返回的surface赋值给self.image
        self.rect = self.image.get_rect()    # 通过其获得相应surface的属性rect,以便将来使用它来指定飞船的位置(这是飞船的rect)

        # 每艘新飞船都放在屏幕底部的中央
        self.rect.midbottom = self.screen_rect.midbottom   # 将飞船的midbottom对应到屏幕的midbottom(自动对应)

# 在pygame里面，原点(0, 0)位于屏幕的左上角，当一个点往右下角移动时，它的坐标值将增大，在1200*800的屏幕上，右下角对应(1200,800)
# 在处理rect对象时，可使用矩形的四个角及中心的x坐标和y坐标，通过设置这些值来指定矩形的位置。居中center、centerx或cnetery，边缘top、bottom、left或right
# 组合midbottom、midtop、midleft和midright
    def blitme(self):
        """在指定位置绘制飞船"""
        self.screen.blit(self.image, self.rect)  # 用blit会将图像绘制到self.rect指定位置


# 通常将游戏元素当作矩形(rect对象)来处理，可以快速判断是否碰撞，玩家几乎注意不到