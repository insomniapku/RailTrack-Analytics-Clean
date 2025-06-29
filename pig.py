from PIL import Image
import os

input_folder = r"D:\01.学习\major\程序设计实习\homework\qt大作业\TripPlanner 0(1)\TripPlanner (1)\build\Desktop_Qt_6_9_1_MinGW_64_bit-Debug\images\railways"         # 输入图层文件夹路径
output_folder = r"D:\01.学习\railways_clean"  # 输出文件夹

os.makedirs(output_folder, exist_ok=True)

for filename in os.listdir(input_folder):
    if filename.endswith(".jpg"):
        path = os.path.join(input_folder, filename)
        image = Image.open(path).convert("RGBA")
        datas = image.getdata()

        new_data = []
        for item in datas:
            # 白色背景 (255,255,255) 变成透明
            if item[0] > 240 and item[1] > 240 and item[2] > 240:
                new_data.append((255, 255, 255, 0))  # 透明
            else:
                new_data.append(item)

        image.putdata(new_data)
        image.save(os.path.join(output_folder, filename))

print("✅ 所有图层已处理为透明背景")
