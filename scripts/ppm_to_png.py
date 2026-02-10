from pathlib import Path
from PIL import Image


def convert_ppm_to_png(images_dir: str = "/images") -> None:
    images_path = Path(images_dir)
    if not images_path.exists() or not images_path.is_dir():
        raise FileNotFoundError(f"Directory not found: {images_path}")

    out_dir = images_path / "png"
    out_dir.mkdir(parents=True, exist_ok=True)

    ppm_files = list(images_path.glob("*.ppm")) + list(images_path.glob("*.PPM"))

    converted = 0
    skipped = 0

    for ppm_path in ppm_files:
        png_path = out_dir / (ppm_path.stem + ".png")

        if png_path.exists():
            skipped += 1
            continue

        try:
            with Image.open(ppm_path) as img:
                img = img.convert("RGB")
                img.save(png_path, format="PNG")
            converted += 1
        except Exception as e:
            print(f"Failed: {ppm_path.name} -> {e}")

    print(f"Done. Converted: {converted}, Skipped (already existed): {skipped}, Total PPM found: {len(ppm_files)}")

if __name__ == "__main__":
    script_dir = Path(__file__).resolve().parent
    project_dir = script_dir.parent
    images_dir = project_dir / "images"
    convert_ppm_to_png(images_dir)