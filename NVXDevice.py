import ctypes

# C error numbers
NVX_ERR_OK = 0  # успешное выполнение функции
NVX_ERR_ID = -1  # неверный ID устройства
NVX_ERR_FAIL = -2  # ошибка при выполнении функции
NVX_ERR_PARAM = -3  # неверный параметр при вызове функции

NVX_DM_NORMAL = 0  # устройство находится в нормальном режиме
NVX_DM_50_KHZ = 1  # устройство находится в режиме 50 кГц


# структура данных для сохранения информации об основных параметрах устройства
class NVXInformation(ctypes.Structure):
    class SYSTEMTIME(ctypes.Structure):
        _fields_ = [
            ('wYear', ctypes.c_int16),
            ('wMonth', ctypes.c_int16),
            ('wDayOfWeek', ctypes.c_int16),
            ('wDay', ctypes.c_int16),
            ('wHour', ctypes.c_int16),
            ('wMinute', ctypes.c_int16),
            ('wSecond', ctypes.c_int16),
            ('wMilliseconds', ctypes.c_int16)]

    _pack_ = 1
    _fields_ = [
        ('Model', ctypes.c_uint16),
        ('SerialNumber', ctypes.c_uint16),
        ('Date', SYSTEMTIME)
    ]


# структура данных для сохранения информации об основных параметрах записи устройства
class NVXProperty(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('RateEeg', ctypes.c_float),
        ('RateAux', ctypes.c_float),
        ('ResolutionEeg', ctypes.c_float),
        ('ResolutionAux', ctypes.c_float),
        ('RangeEeg', ctypes.c_float),
        ('RangeAux', ctypes.c_float)
    ]


# структура данных для сохранения информации о возможностях устройства
class NVXPossibility(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('EegChannelsCount', ctypes.c_uint16),
        ('AuxChannelsCount', ctypes.c_uint16),
        ('InTriggersCount', ctypes.c_uint16),
        ('OutTriggersCount', ctypes.c_uint16),
        ('XDisplayResolution', ctypes.c_uint16),
        ('YDisplayResolution', ctypes.c_uint16),
        ('UserMemorySize', ctypes.c_uint16)
    ]


class NVXFrequencyBandwidth(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('SampleRate', ctypes.c_uint16),
        ('CutoffFreq', ctypes.c_uint16),
        ('DecimFromRate', ctypes.c_uint16),
        ('Decimation', ctypes.c_uint16)
    ]


class NVXDataSettings(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ('DataRate', ctypes.c_ushort),
        ('MainChannels 1', ctypes.c_ushort),
        ('MainChannels 2', ctypes.c_ushort),
        ('MainChannels 3', ctypes.c_ushort),
        ('MainChannels 4', ctypes.c_ushort),
        ('MainChannels 5', ctypes.c_ushort),
        ('MainChannels 6', ctypes.c_ushort),
        ('MainChannels 7', ctypes.c_ushort),
        ('MainChannels 8', ctypes.c_ushort),
        ('MainChannels 9', ctypes.c_ushort),
        ('MainChannels 10', ctypes.c_ushort),
        ('MainChannels 11', ctypes.c_ushort),
        ('MainChannels 12', ctypes.c_ushort),
        ('MainChannels 13', ctypes.c_ushort),
        ('MainChannels 14', ctypes.c_ushort),
        ('MainChannels 15', ctypes.c_ushort),
        ('MainChannels 16', ctypes.c_ushort),
        ('MainChannels 17', ctypes.c_ushort),
        ('MainChannels 18', ctypes.c_ushort),
        ('MainChannels 19', ctypes.c_ushort),
        ('MainChannels 20', ctypes.c_ushort),
        ('MainChannels 21', ctypes.c_ushort),
        ('MainChannels 22', ctypes.c_ushort),
        ('MainChannels 23', ctypes.c_ushort),
        ('MainChannels 24', ctypes.c_ushort),
        ('DiffChannels 1', ctypes.c_ushort),
        ('DiffChannels 2', ctypes.c_ushort),
        ('DiffChannels 3', ctypes.c_ushort),
        ('DiffChannels 4', ctypes.c_ushort),
        ('DiffChannels 5', ctypes.c_ushort),
        ('DiffChannels 6', ctypes.c_ushort),
        ('DiffChannels 7', ctypes.c_ushort),
        ('DiffChannels 8', ctypes.c_ushort),
        ('DiffChannels 9', ctypes.c_ushort),
        ('DiffChannels 10', ctypes.c_ushort),
        ('DiffChannels 11', ctypes.c_ushort),
        ('DiffChannels 12', ctypes.c_ushort),
        ('DiffChannels 13', ctypes.c_ushort),
        ('DiffChannels 14', ctypes.c_ushort),
        ('DiffChannels 15', ctypes.c_ushort),
        ('DiffChannels 16', ctypes.c_ushort),
        ('DiffChannels 17', ctypes.c_ushort),
        ('DiffChannels 18', ctypes.c_ushort),
        ('DiffChannels 19', ctypes.c_ushort),
        ('DiffChannels 20', ctypes.c_ushort),
        ('DiffChannels 21', ctypes.c_ushort),
        ('DiffChannels 22', ctypes.c_ushort),
        ('DiffChannels 23', ctypes.c_ushort),
        ('DiffChannels 24', ctypes.c_ushort)
    ]


class NVXDataModel(ctypes.Structure):
    _pack_ = 1
    _fields_ = [[(f'Data{i}', ctypes.c_int16) for i in range(1, 33)].extend(
        [(f'Aux{1}', ctypes.c_int16) for i in range(1, 5)])].extend([
        ('Status', ctypes.c_uint16),
        ('Counter', ctypes.c_uint16)
    ])


class NVX36:
    def __init__(self):
        self._id = 0  # id нашего текущего устройства
        self._data_mode = ctypes.c_uint16()  # Режим работы устройства (0 - normal, 1 - 50 kHz)
        self._sample_rate_count = ctypes.c_uint16()  # Количество возможных частот дискретизаций устройства
        # храним структуры с информацией об устройстве
        self._nvx_information = NVXInformation()
        self._nvx_property = NVXProperty()
        self._nvx_possibility = NVXPossibility()
        self._nvx_frequency_bandwidth = NVXFrequencyBandwidth()

        # пытаемся загрузить библиотеку
        try:
            # загружаем библиотеку для работы с NVX
            self._lib = ctypes.CDLL('lib/Windows/Generic/x64/Release/nvxmcs.dll')
        except:
            # если библиотека загрузилась неудачно
            self._lib = None
            print('[ERROR] failed to open library (nvxmcs.dll),', end=' ')
            print('check the file location or the architecture version of your device (x64/x86)')

        # начинаем работу с NVX устройством
        res = self._lib.NVXAPIInit()
        if res != NVX_ERR_OK:
            print('[ERROR] cant initialize library resources')

    def get_id(self):
        # получаем количество подключенных устройств
        device_count = self._lib.NVXGetCount()
        if device_count < NVX_ERR_OK:
            print('[ERROR] no devices connected')

        # получаем id устройства с порядковым номером 0 (подключен только один усилитель)
        self._id = self._lib.NVXGetId(0)
        if self._id == 0:
            print('[ERROR] the device ID was not received')

    def open(self):
        # Функция открывает устройство с идентификатором ID
        res = self._lib.NVXOpen(self._id)
        if res == NVX_ERR_ID:
            print('[ERROR] the device is not running, invalid id')
        elif res == NVX_ERR_FAIL:
            print('[ERROR] the device is not running, an error has occurred')

    def close(self):
        # Функция удаляет id заданного устройства. После вызова функции использование этого id становится невозможным
        res = self._lib.NVXClose(self._id)
        if res == NVX_ERR_FAIL:
            print('[ERROR] the device was not closed')

    def api_stop(self):
        # завершаем работу с устройством окончательно (больше не сможем открыть, надо заново инициализировать класс)
        res = self._lib.NVXAPIStop()
        if res == NVX_ERR_FAIL:
            print('[ERROR] the device was not stopped')

    def get_information(self):
        # Функция позволяет получить основные параметры устройств
        res = self._lib.NVXGetInformation(self._id, ctypes.byref(self._nvx_information))
        if res == NVX_ERR_ID:
            print('[ERROR] information not received, invalid device id')
        elif res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_information()')

        return {'Model': ctypes.pointer(self._nvx_information).contents.Model,
                'SerialNumber': ctypes.pointer(self._nvx_information).contents.SerialNumber,
                'Date': {'wYear': ctypes.pointer(ctypes.pointer(self._nvx_information).contents.Date).contents.wYear,
                         'wMonth': ctypes.pointer(ctypes.pointer(self._nvx_information).contents.Date).contents.wMonth,
                         'wDay': ctypes.pointer(ctypes.pointer(self._nvx_information).contents.Date).contents.wDay,
                         'wHour': ctypes.pointer(ctypes.pointer(self._nvx_information).contents.Date).contents.wHour,
                         'wMinute': ctypes.pointer(
                             ctypes.pointer(self._nvx_information).contents.Date).contents.wMinute,
                         'wSecond': ctypes.pointer(
                             ctypes.pointer(self._nvx_information).contents.Date).contents.wSecond}}

    def get_property(self):
        # Функция позволяет получить информацию об основных параметрах записи устройства
        res = self._lib.NVXGetProperty(self._id, ctypes.byref(self._nvx_property))
        if res == NVX_ERR_ID:
            print('[ERROR] property not received, invalid device id')
        elif res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_property()')

        return {'RateEeg': ctypes.pointer(self._nvx_property).contents.RateEeg,
                'RateAux': ctypes.pointer(self._nvx_property).contents.RateAux,
                'ResolutionEeg': ctypes.pointer(self._nvx_property).contents.ResolutionEeg,
                'ResolutionAux': ctypes.pointer(self._nvx_property).contents.ResolutionAux,
                'RangeEeg': ctypes.pointer(self._nvx_property).contents.RangeEeg,
                'RangeAux': ctypes.pointer(self._nvx_property).contents.RangeAux}

    def get_possibility(self):
        # Функция позволяет получить информацию о возможностях устройства
        res = self._lib.NVXGetPossibility(self._id, ctypes.byref(self._nvx_possibility))
        if res == NVX_ERR_ID:
            print('[ERROR] possibility not received, invalid device id')
        elif res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_possibility()')

        return {'EegChannelsCount': ctypes.pointer(self._nvx_possibility).contents.EegChannelsCount,
                'AuxChannelsCount': ctypes.pointer(self._nvx_possibility).contents.AuxChannelsCount,
                'InTriggersCount': ctypes.pointer(self._nvx_possibility).contents.InTriggersCount,
                'OutTriggersCount': ctypes.pointer(self._nvx_possibility).contents.OutTriggersCount,
                'XDisplayResolution': ctypes.pointer(self._nvx_possibility).contents.XDisplayResolution,
                'YDisplayResolution': ctypes.pointer(self._nvx_possibility).contents.YDisplayResolution,
                'UserMemorySize': ctypes.pointer(self._nvx_possibility).contents.UserMemorySize}

    def get_data_mode(self) -> int:
        # Функция передаёт установленный режим работы устройства
        res = self._lib.NVXGetDataMode(self._id, ctypes.byref(self._data_mode))
        if res == NVX_ERR_ID:
            print('[ERROR] data mode not received, invalid device id')
        elif res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_data_mode()')

        return self._data_mode.value

    def get_sample_rate_count(self):
        # Функция передает количество возможных частот дискретизаций устройства
        res = self._lib.NVXGetSampleRateCount(ctypes.byref(self._sample_rate_count))
        if res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_sample_rate_count()')

        return self._sample_rate_count.value

    def get_frequency_bandwidth(self):
        # Функция передает информацию о ширине полосы пропускания устройства
        size = ctypes.c_uint16(self.get_sample_rate_count())
        res = self._lib.NVXGetFrequencyBandwidth(ctypes.byref(self._nvx_frequency_bandwidth), size)
        if res == NVX_ERR_PARAM:
            print('[ERROR] invalid parameter when calling the function get_frequency_bandwidth()')

        return {'SampleRate': ctypes.pointer(self._nvx_frequency_bandwidth).contents.SampleRate,
                'CutoffFreq': ctypes.pointer(self._nvx_frequency_bandwidth).contents.CutoffFreq,
                'DecimFromRate': ctypes.pointer(self._nvx_frequency_bandwidth).contents.DecimFromRate,
                'Decimation': ctypes.pointer(self._nvx_frequency_bandwidth).contents.Decimation}

    def set_data_mode(self, mode: int, settings: NVXDataSettings):
        # Функция предназначена для установки параметров регистрации сигнала. Не используется во время мониторинга и
        # возвращает результат NVX_ERR_FAIL (2.1). Если Mode = 0, то устройство переводится в нормальный режим
        # работы, если Mode = 1, то устройство переводится в режим работы 50 кГц.
        res = self._lib.NVXSetDataMode(self._id, ctypes.c_uint16(mode), ctypes.byref(settings))
        if res == NVX_ERR_FAIL:
            print('[ERROR] impossible to set parameters, recording is underway')
        elif res == NVX_ERR_ID:
            print('[ERROR] data mode not set, invalid device id')

    '''
    Функция переводит устройство в режим мониторинга. Библиотека опрашивает устройство, вводит данные мониторинга
    (отсчеты и состояния триггеров) и буферирует их. Размер буфера рассчитан на 4 секунды при максимальной частоте
    дискретизации
    '''

    def start(self):
        res = self._lib.NVXStart(self._id)
        if res == NVX_ERR_FAIL:
            print('[ERROR] impossible to start device')

    def stop(self):
        # Функция выводит устройство из режима мониторинга
        res = self._lib.NVXStop(self._id)
        if res == NVX_ERR_FAIL:
            print('[ERROR] impossible to stop device')

    def get_data(self):
        res = self._lib.NVXGetData(self._id, )
