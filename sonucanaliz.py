import pandas as pd
import matplotlib.pyplot as plt

# Örnek veri yükleme
data = pd.read_csv('simulation_results.csv')

# PDR hesaplama
data['PDR'] = data['received_packets'] / data['sent_packets']

# Gecikme hesaplama
data['delay'] = data['end_time'] - data['start_time']

# Grafik oluşturma
plt.figure(figsize=(10, 5))

# PDR grafiği
plt.subplot(1, 2, 1)
plt.plot(data['mobility_speed'], data['PDR'], marker='o')
plt.title('PDR vs Mobility Speed')
plt.xlabel('Mobility Speed (m/s)')
plt.ylabel('PDR')

# Gecikme grafiği
plt.subplot(1, 2, 2)
plt.plot(data['mobility_speed'], data['delay'], marker='o', color='r')
plt.title('Delay vs Mobility Speed')
plt.xlabel('Mobility Speed (m/s)')
plt.ylabel('Delay (ms)')

plt.tight_layout()
plt.show()
