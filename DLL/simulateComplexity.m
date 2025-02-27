function simulateComplexity(data)
    % 1) Reemplazar secuencias "\n" por saltos de línea reales
    data = regexprep(data, '\\n', sprintf('\n'));
    
    disp('Cadena recibida:');
    disp(data);
    
    % 2) Separar la cadena en líneas
    linesData = strsplit(data, '\n');
    disp('Líneas extraídas:');
    disp(linesData);
    
    funciones = {};
    complejidades = {};
    
    % 3) Extraer nombre de la función y complejidad de cada línea
    for i = 1:length(linesData)
        line = strtrim(linesData{i});
        if isempty(line)
            continue;
        end
        
        % Patrón esperado: 
        % "Función: <nombre> - Complejidad estimada: O(1)" (o O(n), O(n^2), O(n^3), etc.)
        tokens = regexp(line, 'Funci[oó]n:\s*(.*?)\s*-\s*Complejidad estimada:\s*(O\([^)]+\))', 'tokens');
        if ~isempty(tokens)
            token = tokens{1};
            funciones{end+1} = token{1};      % Nombre de la función
            complejidades{end+1} = token{2};  % Complejidad, ej. "O(n)" o "O(n^2)"
        end
    end
    
    if isempty(funciones)
        disp('No se pudo extraer información de la cadena proporcionada.');
        return;
    end
    
    % 4) Definir el rango de n: de 1 hasta 1000
    n = 1:1000;
    
    % 5) Crear una figura para las curvas
    figure('Name','Curvas de Complejidad','NumberTitle','off');
    hold on;  % Para graficar todas las curvas en el mismo eje
    
    % Generar un mapa de colores para que cada línea tenga un color distinto
    colorMap = lines(length(funciones));
    
    % 6) Para cada función, calcular y graficar la curva de complejidad
    for i = 1:length(funciones)
        c = complejidades{i};  % Por ejemplo, "O(n)" o "O(n^2)"
        fName = funciones{i};    % Por ejemplo, "ArbolAVL::agregarDistancia"
        
        % Inicializamos el vector y con el mismo tamaño que n
        y = zeros(size(n));
        
        % 7) Traducir la notación de complejidad a la función matemática de n
        switch c
            case 'O(1)'
                y = ones(size(n));           % Línea horizontal en 1
            case 'O(n)'
                y = n;                       % Diagonal: si n=2, y=2; n=4, y=4; etc.
            case 'O(n^2)'
                y = n.^2;                    % Si n=2, y=4; n=4, y=16; etc.
            case 'O(n^3)'
                y = n.^3;
            case 'O(n^4)'
                y = n.^4;
            case 'O(n^5)'
                y = n.^5;
            case 'O(n^6)'
                y = n.^6;
            case 'O(log n)'
                y = log2(n);                 % Log base 2
            case 'O(n log n)'
                y = n .* log2(n);            % Producto de n y log n
            otherwise
                y = zeros(size(n));          % En caso de complejidad no contemplada
        end
        
        % 8) Graficar la curva con su color asignado
        plot(n, y, 'Color', colorMap(i,:), 'DisplayName', sprintf('%s - %s', fName, c), 'LineWidth', 2);
    end
    
    % 9) Etiquetas y leyenda
    xlabel('n');
    ylabel('Costo');
    title('Curvas de Complejidad');
    legend('Location','best');
    
    % Forzar que ambos ejes tengan el mismo rango: de 1 a 1000
    xlim([1, 1000]);
    ylim([1, 1000]);
    axis equal;  % Para que la escala en x e y sea la misma
    
    hold off;
end
