import sys       # 导入系统模块，调用它，真正进入底层
import pygame

from settings import Settings
class AlienIncasion:
    """管理游戏资源和行为的类"""
    def __init__(self):
        """初始化游戏并创建游戏资源"""
        pygame.init()    # pygame.init()函数初始化背景

        self.clock = pygame.time.Clock()    # 先定义这个时钟，创建pygame.time模块重点Clock类的一个实例，在run_game()的while循环末尾让这个时钟进行计时

        self.settings = Settings()   # 创建一个Settings实例，好去调用它的方法，拿它的self参数

        # 将属性赋值给self.screen，让这个类的所有方法都能使用它,注意，类里面不同函数方法也有参数隔离，而加了self化可以通用，而且状态会改变
        # 赋给属性self.screen的对象是一个surface。在Pygame里面，surface是屏幕的一部分，用于显示游戏元素，这个游戏每一个元素都是一个surface
        # display.set_mode()返回的surface表示整个游戏窗口，激活游戏动画循环后，每经过一次循环都将自动重绘这个surface，将反映呈现

        self.screen = pygame.display.set_mode((self.settings.screen_width, self.settings.screen_height))  # pygame.display.set_mode()创建一个显示窗口，实参(1200,800)是一个元组(注意加括号)，制定了游戏窗口尺寸——宽1200像素、高800像素
        pygame.display.set_caption("Alien Invasion") # pygame.display.set_caption()设置游戏窗口标题

        # display.set_mode()创建的surface对象是一个空白窗口，默认背景是黑色。要想改变背景颜色，需要使用fill()方法填充颜色
        # fill()方法需要一个颜色实参，Pygame使用RGB颜色模式表示颜色。RGB模式使用红、绿、蓝三种颜色的不同强度来表示其他颜色。每种颜色的强度用0~255之间的整数表示


        # pygame.display 是一个子模块
    def run_game(self):
        """开始游戏的主循环"""
        while True:      # 这个不断地循环包含一个事件的循环以及管理屏幕更新的代码。事件是由用户玩游戏时执行的操作，如按键或移动鼠标。
            # 侦听键盘和鼠标事件
            for event in pygame.event.get():   # 嵌套的for循环是一个事件循环，以侦听事件并根据发生的事件类型执行适当的任务，为了响应事件
                # 使用pygame.event.get()来访问Pygame检测到的事件，这个函数返回一个列表，其中包含它上一次调用后发生的所有事件。所有键盘和鼠标事件都导致for循环运行
                if event.type == pygame.QUIT: # 使用if语句来检测并响应特定的事件，如果响应状态是点击关闭按钮，检测到pygame.QUIT状态，就调用sys.exit()
                    sys.exit()

            # 每次循环时都重绘屏幕
            self.screen.fill(self.settings.bg_color)  # 调用fill()方法用这种背景色填充屏幕。fill()方法用于处理surface，只接受一个表示颜色的实参


            # 让最近绘制的屏幕可见
            pygame.display.flip()   # 调用display.flip()命令Pygame让最近绘制的屏幕可见(翻页)。这里，他在每次实行while循环时都绘制一个空屏幕，并擦去旧屏幕，
            # 这样我们在移动游戏元素时，pygame.display.filp()将不断更新屏幕，以显示新位置上的元素并隐藏原来位置上的元素

            self.clock.tick(60)     # time.Clock()中time模块的Clock类中的tick方法接受一个参数:游戏的频率。Pygame将尽可能确保这个循环每秒恰好运行60次

if __name__ == '__main__':  # 仅当直接运行该文件执行
    # 创建实例并运行游戏
    ai = AlienIncasion() 
    ai.run_game()