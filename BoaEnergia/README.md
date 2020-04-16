# Boa Energia: Brazil Public Energy Consumption Database
This repository contains energy consumption data from a Brazilian household.
Consumption and Temperature data were collected from February 2nd, 2020 to March 3rd, 2020 (period of 28 days).

Measurements were performed each second, and the consolidated data was registered with hour granularity. It has total power consumption, air conditioner, shower, and lightning energy consumption data, estimated from current measurements.

Its main application is for energy prediction algorithm development.

[//]: # (For an overview of the data collection procedures, see:)

[//]: # (All those wishing to reference the data set in academic work should
cite this paper.)

We welcome any comments or questions about the data:
Victor Hayashi (victor.hayashi@usp.br)

## Raw Data

Data present on /raw folder are the raw data, one file per day, just the way the developed smart meter registered in its local filesystem.

## Consolidated Data

Consolidated data were created from raw data, and their desciption are presented below.

### BoaEnergia.csv File

- **data**: day from timestamp, DD/MM/YYYY format
- **horario**: hour of day, 0 to 23
- **kwh_hcanal1**: estimated consumption in kVAh from channel 1 (the sum of channels 1 and 2 equals total power consumption)
- **kwh_hcanal2**: estimated consumption in kVAh from channel 2 (the sum of channels 1 and 2 equals total power consumption)
- **chuveiro**: estimated consumption in kVAh from eletric shower
- **arcond**: estimated consumption in kVAh from air conditioner
- **ilum1**: estimated consumption in kVAh from lightning 1 (the sum of illum 1 and 2 equals total lightning consumption)
- **ilum2**: estimated consumption in kVAh from lightning 2 (the sum of illum 1 and 2 equals total lightning consumption)
- **tem_h_med**: average temperature in ºC
- **tem_h_min**: minimum temperature in ºC
- **tem_h_max**: maximum temperature in ºC
- **kwh_total**: estimated total consumption in kVAh

[//]: # (### BoaEnergiaFormatado.csv)

[//]: # (The same as BoaEnergia.csv file, with unix timestamp.)

[//]: # (### BoaEnergiaValidacao.csv)
