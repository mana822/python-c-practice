import pytest
from survey import AnonymousSurvey
@pytest.fixture  # 它下面的函数就是一个夹具函数，pytest会自动运行它(被动)，并将其返回值传递给测试函数
def language_survey():
    """一个可供所有测试函数使用的AnonymousSurvey"""
    question = "What language did you first learn to speak?"
    language_survey = AnonymousSurvey(question)  # 创造实例时执行的是__init__里面的程序
    return language_survey    # 这里直接返回实例对象，后面测试函数直接调用这个夹具就可以使用这个实例对象了(相当于直接给指针了)

def test_store_single_response(language_survey): # 当测试函数的形参与夹具函数的名字相同时，pytest会自动运行夹具函数，并将其返回值传递给测试函数
    """测试单个答案会被妥善保管"""                 # 如果夹具函数没有返回值，则会将None传递给测试函数
    language_survey.store_response('English')
    assert 'English' in language_survey.responses

def test_store_three_responses(language_survey):  # 只要函数前缀是test_，pytest就会自动运行它，而形参则是由夹具先判断，如果与夹具函数相同则会自动运行夹具函数，并将其返回值传递给测试函数
    """测试三个答案会被妥善存储"""                 # 记住，夹具函数的运行是被动的，它晚于测试函数被调度，却早于测试函数执行，只有当测试函数需要它时，它才会被调用
    responses = ['English', 'Spanish', 'Mandarin']
    for response in responses:
        language_survey.store_response(response)
    for response in responses:
        assert response in language_survey.responses