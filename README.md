# **scorewarrior**
**Краткое описание**   
   
**scorewarrior/models/actions/IAction.h** - Содержит базовый интерфейс для всех команд.    
**scorewarrior/models/actions/builders/ActionBuilder.h** - Билдеры для команд   
**scorewarrior/models/actions/builders/ActionFactory.h** - Фабрика для команд, по сути обертка над билдерами. Создана для удобства чтения команд из источников (сейчас это стринг)   
**scorewarrior/models/objects/Object.h** - базовый класс для всех обектов. Его насделует Attacker->Warrior. Для реализации дальнобойных обектов, достаточно добавить класс Range унаследовать от Attacker - добавить логику на определения расстояния   
**scorewarrior/models/Map.h** - карта с айдишниками объектов - обернута в синглтон   
**scorewarrior/models/Tick.h** - имплементация тиков - обертута в синглтон   
**scorewarrior/controller/Controller.h** - контроллер логики. Пока монолит. но при росте логики, имеет смысл разбить на интерфейсы.

#    
**Build**   
```
mkdir build && cd build   
cmake ..   
make
```
