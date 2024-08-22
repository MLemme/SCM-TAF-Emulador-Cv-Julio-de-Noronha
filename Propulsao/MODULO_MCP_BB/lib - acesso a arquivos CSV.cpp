
int countCampoCSV ( AnsiString linha, char separador )
{
   int retorno = 1;

   for ( int i = 1; i <= linha.Length(); i++ )
      if ( linha[i] == separador )
         retorno++;

   return retorno;
}

AnsiString getCampoCSV ( AnsiString linha, int campo, char separador )
{
   // A Fun��o foi escrita para auxiliar na leitura de arquivos formatados como campos separados por um caracter.
   // Funcionamento:
   // 1- S�o passados como par�metros uma "linha", o n�mero do "campo" desejado, contando da esquerda
   //    para direita a partir de 0, e o caracter "separador" de campos.
   // 2- Se a "linha" estiver vazia ou se o campo requisitado for maior que o n�mero de campos existentes, a fun��o
   //    retorna uma string vazia. Sen�o, a fun��o retorna uma string contendo o campo requisitado.

   int
      numCampo = 0,
      inicioCampo = 1,
      tamCampo = 0,
      qtdCampos = countCampoCSV ( linha, separador );

   AnsiString
      retorno = "";


   if (   linha.Length() &&
        ( campo > -1 ) &&   
        ( campo < qtdCampos ) &&
        ( ! ( ( campo == 0 ) && ( linha[1] == separador ) ) ) &&
        ( ! ( ( campo == qtdCampos -1 ) && ( linha[ linha.Length() ] == separador ) ) )
      )
   {
      for ( int i = 1; i <= linha.Length() && ( numCampo != campo ); i++ )
         if ( linha[i] == separador )
         {
            numCampo++;
            inicioCampo = i + 1;
         }

      if ( linha[ inicioCampo ] != separador )
         while ( ( inicioCampo + tamCampo <= linha.Length() ) && ( linha[ inicioCampo + tamCampo ] != separador ) )
            tamCampo++;

      retorno = linha.SubString( inicioCampo, tamCampo );
   }

   return retorno;
}
