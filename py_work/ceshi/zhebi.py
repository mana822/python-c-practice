x = "我是全局变量"

def test_shadow():
    print("--- 准备打印 x ---")
    print(x)        # 🚨 这里会报错 UnboundLocalError
    print("--- 打印结束 ---")
    x = "我是局部变量"  # 🚨 因为这一行的存在，Python 把整个函数里的 x 都当成了本地的

print("--- 运行场景一 ---")
try:
    test_shadow()
except UnboundLocalError as e:
    print(f"报错啦：{e}")


y = "我是全局变量"

def test_read_only():
    print("--- 运行场景二 ---")
    print(y)  # ✅ 完全没问题。因为函数里没有任何 y = ...，所以它去外面借了全局的 y

test_read_only()


def test_block_scope():
    print("--- 运行场景三 ---")
    if True:
        block_var = "我在 if 里面定义的"
    
    # 🚨 在 C 语言里，这行代码会报错，因为 block_var 出不了大括号
    # 但在 Python 里，这行代码畅通无阻！
    print(block_var) 

test_block_scope()



z = "全局的 z"

def fix_with_placeholder():
    print("--- 运行场景四：占位法 ---")
    z = None  # ✅ 进门先占坑，本地的 z 有值了
    print(z)  # 打印 None
    z = "局部的 z"
    print(z)  # 打印 局部的 z

def fix_with_global():
    print("--- 运行场景四：global法 ---")
    global z  # ✅ 向解释器宣告：别搞本地户口，我盯上外面那个 z 了！
    print(z)  # 打印 全局的 z
    z = "我改了全局的 z"
    print(z)  # 打印 我改了全局的 z

fix_with_placeholder()
fix_with_global()
print(f"外面看一眼全局的 z：{z}") # 被 fix_with_global 改了