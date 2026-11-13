# 使用pytest针对get_formatted_name()函数的测试如下:
from name_function import get_formatted_name  # 导入要测试的ger_formatted_name()函数

def test_first_last_name():    # 测试文件的名称很重要，必须以test_，定义一个测试函数
    """能够正确处理吗"""
    formatted_name = get_formatted_name('janis', 'jolin')    # 调用测试函数，正常传递参数，要有返回值才能接住
    assert formatted_name == 'Janis Jolin'   # 断言(assertion)就是声称满足特定的条件:这里声称formatted_name的值为'Janis Joplin'。

def test_first_last_middle_name():
    formatted_name = get_formatted_name('wolfgang', 'mozart', 'amadeus')
    assert formatted_name == 'Wolfgang Amadeus Mozart'   # 注意实参顺序别反了
