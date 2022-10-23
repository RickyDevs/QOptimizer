.pragma library


var mainModelData = [
            {
                query: 'SELECT * FROM Win32_Processor',
                fields: ['Name']
            },
            {
                query: 'SELECT * FROM Win32_OperatingSystem',
                fields: ['TotalVirtualMemorySize']
            }

];


var mainModelData2 = [
            {
                value: 'Processors',
                icon: 'qrc://processor.png',
                childs: [
                    {
                        query: 'SELECT * FROM Win32_Processor',
                        fields: ['Name']
                    }
                ]
            },
            {
                value: 'Memory',
                icon: 'qrc://memory.png',
                childs: [
                    {
                        query: 'SELECT * FROM Win32_OperatingSystem',
                        fields: ['TotalVirtualMemorySize']
                    }
                ]
            }

        ];
