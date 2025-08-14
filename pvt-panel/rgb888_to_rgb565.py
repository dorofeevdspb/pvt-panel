#!/usr/bin/env python3
"""
rgb888_to_rgb565.py
Пост-обработка EEZ Studio: заменяем 0xRRGGBB -> 0xXXXX (RGB565)
Запуск: python rgb888_to_rgb565.py
"""

import os
import re
import glob

SRC_DIR = "src"          # папка с исходниками
BACKUP_EXT = ".bak"      # расширение для резервных копий

def rgb888_to_rgb565(hex_str: str) -> str:
    """
    Конвертирует строку '0xRRGGBB' или '0xFFRRGGBB' в '0xXXXX' (RGB565).
    """
    # убираем 0x и возможный префикс FF
    val = hex_str.lower().replace("0x", "")
    if len(val) == 8:
        val = val[2:]  # 0xFFRRGGBB -> RRGGBB
    if len(val) != 6:
        return hex_str  # не трогаем, если формат неожиданный

    r = int(val[0:2], 16)
    g = int(val[2:4], 16)
    b = int(val[4:6], 16)

    # RGB565: RRRRR GGGGGG BBBBB
    rgb565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)
    return f"0x{rgb565:04X}"

def process_file(path):
    with open(path, encoding="utf-8") as f:
        data = f.read()

    # ищем литералы 0xRRGGBB или 0xFFRRGGBB
    pattern = re.compile(r'\b0x(?:[0-9a-fA-F]{6}|[0-9a-fA-F]{8})\b')
    new_data, n = pattern.subn(lambda m: rgb888_to_rgb565(m.group(0)), data)

    if n:
        # создаём бекап
        os.rename(path, path + BACKUP_EXT)
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_data)
        print(f"{path}: заменено {n} литералов")

def main():
    for ext in ("*.c", "*.cpp", "*.h", "*.hpp"):
        for file in glob.glob(os.path.join(SRC_DIR, "**", ext), recursive=True):
            process_file(file)

if __name__ == "__main__":
    main()