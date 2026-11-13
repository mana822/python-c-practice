class AnonymousSurvey:
    """收集匿名调查问卷的答案"""
    def __init__(self, question):
        """存储一个问题，并为存储答案做准备"""
        self.question = question
        self.responses = []

    def show_question(self):
        """显示调查问卷"""
        print(self.question)

    def store_response(self, new_response):
        """存储单份调查答案"""
        self.responses.append(new_response)
        
    def show_results(self):
        """显示收集到的所有答案"""
        print("Survey results: ")
        for response in self.responses: # 只要是能被直接被实例调用到的变量要self化，而内部变量只能通过返回值拿到，内部变量通常是参与内部运行，没必要展现
            print(f"-{response}")