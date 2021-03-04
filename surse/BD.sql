-- 11

SELECT last_name, department_id 
FROM employees
WHERE department_id IN (10,30)
ORDER BY last_name;

-- 13

select sysdate 
from employees; -- afiseaza data de n ori, n = nr de intrari din tabelul employees

DESC DUAL;
SELECT *FROM DUAL; -- pseudo-tabel

select sysdate
from dual;

TO_CHAR(data, format) -- functie de conversie(converteste o data cal. in char, dupa un anumit format)

select to_char(sysdate, 'dd')
from dual;

select to_char(sysdate, 'd')
from dual;

select to_char(sysdate, 'ddd')
from dual;

select to_char(sysdate, 'hh12 mi ss sssss') "ora/minut/secunda"
from dual;


-- 14

-varianta 1
-- operatorul LIKE impreauna cu %
SELECT last_name, hire_date
FROM employees
WHERE hire_date LIKE("%87%");


-varianta 2

SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY')='1987';


-- 18

SELECT last_name
FROM employees
WHERE upper(last_name) LIKE '__A%';

SELECT last_name
FROM employees
WHERE lower(last_name) LIKE '__a%';

-- 19

SELECT last_name
FROM employees
WHERE upper(last_name) LIKE '%L%L%' and department_id = 30 OR manager_id = 102;

-- 15

SELECT last_name, job_id
FROM employees
WHERE manager_id IS NULL; -- IS/ IS NOT 

-- 16

SELECT last_name, salary, commission_pct
FROM employees
WHERE commission_pct IS NOT NULL
ORDER BY salary desc, commission_pct desc;


-- 17
Select last_name, salary, commission_pct
from employees
order by salary, commission_pct;

--2.

SELECT initcap(first_name) "PRENUME", upper(last_name) "NUME", length(last_name) "LUNGIME NUME"
FROM employees
WHERE  upper(last_name) LIKE 'M%' OR upper(last_name) LIKE 'J%' -- angajati al caror nume incepe cu J sau M
       OR upper(last_name) LIKE '__A%' -- au a treia litera din nume A
ORDER BY length(last_name) desc;


SELECT initcap(first_name) "PRENUME", upper(last_name) "NUME", length(last_name) "LUNGIME NUME"
FROM employees
WHERE  upper(last_name) LIKE 'M%' OR upper(last_name) LIKE 'J%' -- angajati al caror nume incepe cu J sau M
       OR substr(upper(last_name), 3, 1) = 'A' -- au a treia litera din nume A
ORDER BY length(last_name) desc;


-- 4
-- pozitia din nume in care apare prima data litera 'a'
INSTR(string, 'chars' [,start [,n]]) -> instr(upper(last_name),'A',1,1)

-- angajati ai caror nume se termina cu 'e'
SUBSTR(string, start[,n]) -> substr(lower(last_name),-1) = 'e'

Select employee_id "Id Ang", last_name "nume", length(last_name) "lung nume", 
        instr(upper(last_name),'A',1,1) "pozitie litera in nume"
from employees
where substr(lower(last_name), -1) = 'e'

--

