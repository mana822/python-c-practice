import json

# 1. 定义一个 Python 字典对象（内存里的实体）
py_dict = {
    "name": "赛博独狼",
    "age": 18,
    "is_geek": True,
    "skills": ["C", "Python", None]
}

print("--- 1. 打印 Python 对象 ---")
print(py_dict)
print(type(py_dict)) # <class 'dict'>

# 2. 序列化（Python 对象 -> JSON 字符串）
json_str = json.dumps(py_dict)

print("\n--- 2. 打印 JSON 字符串 ---")
print(json_str)
print(type(json_str)) # <class 'str'> ！