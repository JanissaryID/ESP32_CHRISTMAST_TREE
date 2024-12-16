void heatSetup(){
  heat = new byte*[dimensionTree[0]];
  for (int i = 0; i < dimensionTree[0]; i++) {
    heat[i] = new byte[dimensionTree[1]];  // Membuat baris untuk setiap kolom
  }
}

void Fire2012() {
  // Langkah 1: Redam panas setiap sel
  for (int x = 0; x < dimensionTree[0]; x++) {
    for (int y = 0; y < dimensionTree[1]; y++) {
      heat[x][y] = qsub8(heat[x][y], random8(0, 5));  // Kurangi panas secara acak
    }
  }

  // Langkah 2: Panas menyebar dari bawah ke atas
  for (int x = 0; x < dimensionTree[0]; x++) {
    for (int y = dimensionTree[1] - 1; y > 0; y--) {
      heat[x][y] = (heat[x][y] + heat[x][y - 1] + heat[x][y - 1] + heat[x][y - 2]) / 4;
    }
  }

  // Langkah 3: Tambahkan panas baru di baris paling bawah
  for (int x = 0; x < dimensionTree[0]; x++) {
    if (random8() < 50) {  // Tambahkan panas secara acak
      heat[x][0] = qadd8(heat[x][0], random8(160, 255));  // Panas maksimum
    }
  }

  // Langkah 4: Konversi panas menjadi warna
  for (int x = 0; x < dimensionTree[0]; x++) {
    for (int y = 0; y < dimensionTree[1]; y++) {
      byte colorIndex = scale8(heat[x][y], 240);  // Skala panas ke warna
      ledsTree[XY(x, y)] = ColorFromPalette(HeatColors_p, colorIndex);
    }
  }
}