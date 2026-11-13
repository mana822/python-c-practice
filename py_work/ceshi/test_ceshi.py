from ceshi import Employee    # 文件名--里面的元素(什么都能拿)


message = Employee('ma', 'na', 2999)
def test_give_default_raise():
    assert message.firstname == 'ma' and message.lastname == 'na' and message.money == 2999
    # assert后面可以有两个参数，一个是断定的数，一个是错误后输出的内容
def test_give_custom_raise():
    append = message.give_raise()
    assert append == 7999

