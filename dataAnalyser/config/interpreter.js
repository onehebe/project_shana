lines = text.split(/\r\n|[\r\n]/);
regReal = "[+-]?[\\d]+([\\.][\\d]*)?([Ee][+-]?[0-9]{0,2})?";
i=0; 
j=0;
len = lines.length;
for(i=0;(lines[i]!=="Point,Zap voltage,Measurement voltage(Average),Measurement current(Average),Leak current") && (i<len);i++)
{
    ;
};
if(i>=len-1)
{
    status = false;
}
else
{
    status = true;
}

i++;
for(j=0;j<len-i-1;j++)
{
	tempData = lines[j+i].split(',');
	count[j] = tempData[0];
	zap[j] = tempData[1];
	current[j] = tempData[3];
	voltage[j] = tempData[2];
	leakage[j] = tempData[4];
}
